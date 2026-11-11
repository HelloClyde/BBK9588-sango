# 游戏内彩色素材

1240帧均有彩色PNG：原库1202帧、补充底栏和竖屏制作群组2帧、势力选择背景/33张君主预览头像/选中条35帧，以及游戏设置底图1帧。图案去重后为690种，沿用GPT Image图集、木色编辑母图和后续势力页/设置页母图，再按记录裁切到原生尺寸。原始灰度素材和 `../drafts/color9288s/` 三张既有草稿保留。

| 路径 | 内容 |
| --- | --- |
| `library/` | 按原资源实际代码用途及人物姓名命名的彩色帧，目录/帧名对应 `../library/` |
| `statusbar/`、`credits/` | 两项补充素材的彩色目标图 |
| `references/` | 从原始PNG机械排版的灰度图集或整页参考 |
| `generated/` | 选用的GPT Image高清彩色母图，另保留制作群组文字校正前的生成版本 |
| `prompts/` | 对应提示词；制作群组文字校正另有初稿提示词 |
| `catalog.json` | 每帧原资源ID、子图、帧号、原路径、尺寸、别名、色图、裁切框和SHA-256 |

图片名称沿用代码用途核对的结果，不根据上色后的外观重新猜测用途。原版未定位调用的资源仍保留待确认标记；空白帧、文字、光标等保留其原用途和形状。程序署名为通宵虫、南方小鬼，美工Sunday。

## 编辑、导入与构建

```powershell
python tools/color_assets.py status
# 修改现有原生尺寸PNG后更新其记录，再完整构建
python tools/color_assets.py refresh
python build.py
# 也可只重打彩色包
python tools/color_assets.py build
# 新生成母图按记录中的图集格子导入
python tools/color_assets.py import portraits-00 PATH/TO/generated.png
```

正常构建从仓库里的目标PNG编码，不调用图像生成服务。完整导入是正常构建的前提；`--allow-partial` 只供开发期局部验证。导入只做裁切、尺寸转换和文件编码，实际上色由GPT Image完成。重复原图的别名导入时共用相同结果。

```powershell
python -m pip install -r requirements-assets.txt -r requirements-validation.txt
python tools/test_color_assets.py
```

`python tools/test_strategy_color_map.py` 另检验10帧城市透明键、18个视口的240×232完整覆盖、增量重画及灰度回退。彩色地图仅在绘图时把原7×7逻辑格映射到240×232，底栏仍在y=232，城市选择/滚动规则不变。

编译MIPS检查覆盖全部1239帧查找、RGB565字节、140张战斗精灵的原遮罩、屏幕/上下文绘制、裁切、缺包和损坏包、分配失败及文件清理。固件界面范围见根目录验证记录。

## sango.clr 格式和加载

`build/sango.lib` 仍保留全部原资源、透明遮罩和动画时间轴，字节不因上色变化。CLR必须与它一起安装到 `应用/数据/游戏/`。BDA通过SDK命名接口读取同目录的CLR并绘制RGB565，不写GUI表或直接操作帧缓冲。缓存独立于旧存档区，约2.19MiB；缺包、错误大小/索引、LIB大小或CRC32不匹配、内存不足时回退原灰度路径。

所有整数为小端。文件头32字节：

| 偏移 | 类型 | 意义 |
| --- | --- | --- |
| 0 | 8字节 | `SGCOLOR1` |
| 8 | uint32 | CLR总字节数 |
| 12 | uint32 | 索引项数，当前1204 |
| 16 | uint32 | 索引起点，32 |
| 20 | uint32 | RGB像素区起点，32+项数×16 |
| 24 | uint32 | 配套LIB字节数 |
| 28 | uint32 | 配套LIB完整CRC32 |

每个16字节索引项是 `<IIHHI>`：原LIB帧像素偏移、CLR像素偏移、宽、高、原flags；按原LIB偏移严格递增。像素是逐行RGB565、每像素2字节，完全相同的帧共享像素区。flags低位保留原flags，未带0x100位时，mask位继续读取原LIB的2bpp透明遮罩；带0x100位时，以RGB565的0值为完整透明遮罩，不再叠加旧LIB遮罩。带此位的帧将不透明纯黑编码为0x0001，避免混淆。原有RGBA遮罩仍以原LIB为准。资源055原本没有透明遮罩，彩色版在catalog中另声明edge-connected-white：只将与边缘连通的近白背景编码为透明键，保留封闭的白色窗户/屋顶细节。原PNG及原LIB不变。原生上下文复制使用0作为透明键，因此不透明纯黑通过SDK助手转换为0x0001。

来源和许可边界见 [声明](../../THIRD_PARTY_NOTICES.md)。

资源056选择箭头的原始遮罩有损坏，会露出79个白底像素、遮掉37个箭头像素。catalog的`original-color-plane`规则从原PNG保留的完整颜色平面解码68个箭头像素，以金色调色板编码，白色背景为透明键；旧LIB、原PNG和此前生成PNG均保留，运行时以此解码结果为准。测试覆盖49个格子、四向重画和原生上下移动/返回，单独验证背景没有被白色覆盖。

战场资源004按 `sango_battle_terrain_at` 的实际分类补色：平原/草地/森林/山地为有底色的完整图块，16～40及42～45为蓝色水域，41为村庄。地形保持原16×16尺寸和图块顺序，初稿和河道校正母图均保留。alpha.4进一步修正母图上色导致的岸线偏移，具体打包规则见下文。

资源009天气用边缘连通的近白透明规则，资源015伤害数字用全部近白透明规则（包含0/8的封闭字腔），以免在彩色面板上出现白方块。原战斗兵种、光标、140张演出精灵的原遮罩保持不变。

彩色动画播放通过SDK兼容上下文保存底图，过期精灵的矩形恢复原像素；原播放速度、指令、输入返回值及末帧保留行为不变。每次播放额外申请约150KiB底图上下文，结束或按键中断时释放，分配失败仍按原擦除路径播放。`python tools/test_battle_color.py` 检查17组战斗时间轴与上下文清理。

`battle-forest-green`把资源004图块005的树冠改为绿色；`battle-hud-sharp`只优化资源008、017图片中的粮、天、信息、查找，不增减状态栏行数。底栏图集用最近邻导入，避免缩到原生尺寸时再次软化字形；母图、提示词和既有版本均保留。

运行时仍按图片绘制固定标签、分隔线及花纹。粮草数字和右侧单行动态文本用SDK透明文字叠加；右侧沿用原版的切换：光标有部队显示姓名，空地显示地形。更新文本时从原图片局部恢复背景，不填白色矩形。彩色战斗演出框按原130×64尺寸置于战场中间(55,80)，动画、提示及伤害数字共用相同位移。

上一版底栏采用常规字重（保留作对照）：[选用母图](generated/battle-hud-sharp.png)、[减细提示词](prompts/battle-hud-regular.txt)。此前[粗体母图](generated/battle-hud-sharp-bold.png)与[初次清晰化提示词](prompts/battle-hud-sharp.txt)均保留。全部通过内置GPT Image编辑，导入脚本仅裁切和缩放。

## 最终像素网格与1:1状态图

当前状态图是[240×24 PNG](battle-ui/status-row-240x24.png)，按钮是[240×36 PNG](statusbar/toolbar-240x36.png)。GPT Image只生成[无文字的美术底图](generated/gold-ui-battle-hud-smooth.png)，[提示词](prompts/gold-ui-battle-hud-smooth.txt)保留；固定的粮、天、信、息、查、找使用[6张16×16单比特字形](battle-ui/glyphs/)在导出PNG时按整数坐标贴入，字形不经过任何缩放或抗锯齿。程序只复制整张成品图，不按字形绘制固定标签，状态图不再走旧3:2采样。

```powershell
# 使用已入库的背景和字形，重新烘焙两张最终PNG；无需安装字体
python tools/compose_battle_ui.py
# 仅重新排字时在Windows上运行；字体和文件哈希须匹配来源记录
pwsh -File tools/typeset_battle_ui.ps1
python tools/compose_battle_ui.py
python build.py
python tools/test_battle_pixel_grid.py
```

PNG为可编辑素材，合成脚本只在素材制作时使用。正常构建只编码已入库的PNG，不依赖Windows字体或图像生成服务。上一版粗体、常规字重母图均保留。

SGCOLOR1的1204条原索引保持不变，可选的原尺寸状态图追加在索引像素区之后，文件末尾32字节为`<8sIIIIII>`：`SGHUD01\0`、像素偏移、像素字节数11520、宽240、高24、原资源008帧偏移、该像素区CRC32。原尺寸图为RGB565小端，不计入原1204条索引。读取时核对边界、尺寸、来源索引及CRC；没有此尾部的旧CLR继续按原路径显示。

## 既有金色UI方案

既有金色方案采用金色边框、浅金纸底和深金/铜色纹饰；其中主菜单现已由下述木色方案替换。该配色依据用户偏好，原灰度素材不能证明历史原版颜色。主菜单、剧本、存读档、制作群组和共享底栏的5张GPT Image编辑母图与提示词记录在 [gold-ui-provenance.json](gold-ui-provenance.json)。固定字形仍按1:1烘焙，位置保持“粮”x=4、“天”x=82。人物/地图/战斗图标不做统一色调处理，选中菜单的深色对比保留。此前红绿母图、提示词、原生PNG和排版记录位于 `variants/red-green-ui/`，也可按提交2519f33追溯。

## 开场与主菜单木色方案

开场门（资源003）和主菜单（资源044）改用旧胡桃木、榆木色和深浅木雕纹饰。主菜单四项的普通态、选中态（资源100～103，共8帧）同步采用浅木黑字、深木浅字。后续补齐制作群组、存读档、历史时期页及其选中动画；主菜单第三项改为游戏设置，新增同风格二级页。其他未涉及界面延续上述金色方案。木色由内置 GPT Image 编辑生成，导入时仅裁切与转换尺寸；没有在运行时叠加色调。

三张高清母图位于 `generated/wood-ui-opening-door.png`、`generated/wood-ui-main-menu.png`、`generated/wood-ui-menu-states.png`；对应完整提示词位于 `prompts/` 同名 TXT。原生 PNG、生成来源和哈希见 [wood-ui-provenance.json](wood-ui-provenance.json)。此前的开场、金色菜单及选中态母图和原生帧均保存在 `variants/gold-before-wood/`。

10帧图片更新，其余1194帧不变。资源ID、240×320页面、126×57按钮、原LIB及开门/选中时间轴保持不变。8帧按钮外侧与边缘连通的白色底角在CLR打包时转为透明，封闭的浅木面板和文字保留不透明，避免木色背景上出现白角。所有改色均在素材内完成，沿用D4的菜单、音乐和存档修复。

木色版后续另补充了程序中的左右开门过渡，沿用同一门图，不新增或改写图片帧；实现、原版对照边界和运动验证见 [开门动画](../../docs/OPENING_ANIMATION.md)。

设置页与木色补齐共更新14帧原生图片，新增078号设置底图。母图、提示词和精确裁切框见 [wood-settings-provenance.json](wood-settings-provenance.json)，以前版本保存在 `variants/before-wood-settings/`。制作群组图片底部的“优化作者 HelloClyde”已烘焙在素材内。`python tools/prepare_wood_settings_assets.py` 可重新导入这些母图；开关状态与音量百分比由原生透明字形绘制，固定标题和按钮文字来自图片。

## 势力选择木质页与君主预览

势力选择使用同风格底图、48×48君主头像和深木色选中条（资源052、053、077）。背景由GPT Image生成，头像从对应剧本原有高清母图裁切，未放大24像素PNG。50个剧本君主选择的姓名、原头像ID和33张预览帧的映射由实际城市归属与代码确定。素材、裁切和提示词见 [来源记录](../ruler/provenance.json)，使用和验证见 [势力选择](../../docs/RULER_SELECTION.md)。

当前UI美术以连续曲线/明暗重绘，去除此前母图中放大的像素块；固定文字仍使用已入库的16×16单比特掩码按1:1导出。该细化覆盖菜单、剧本、存读档、制作群组和共享底栏，未对小头像/城市/战斗精灵批量滤波或换色。选用5张母图及6份提示词见 `gold-ui-provenance.json`；原金色颗粒版本在 `variants/gold-pixel-ui/`。

## 原生问号与天气图（alpha.3）

问号用同套SimSun16单比特字形排入240×24状态图，文件为 `battle-ui/glyphs/question_16x16.png`；图框也在素材导出时对齐整数像素。运行时只复制图片。
天气5态由内置GPT Image按原图形与编号重制，保留原12×12索引供旧包/灰度回退；新成品位于 `battle-ui/weather/`，均18×18、四种RGB颜色、二值alpha，运行时不缩放。母图 `generated/weather-native-sharp.png`、[提示词](prompts/weather-native-sharp.txt)、[来源与导出记录](battle-ui/weather/provenance.json)均入库；旧状态图保留在 `variants/alpha2-hud/`。

```powershell
python tools/import_native_weather.py
python tools/compose_battle_ui.py
python build.py
python tools/test_battle_info.py
python tools/test_battle_pixel_grid.py
```

CLR的SGHUD01状态像素前追加天气像素3240字节及32字节`<8sIIIIII>`描述：`SGWTH01\0`、像素偏移、3240、18、18、原资源009首帧像素偏移、CRC32。五帧按原编号顺序，每帧648字节，RGB565零值表示透明。加载时核对边界、尺寸、源索引与CRC。没有该块的旧CLR继续走原兼容路径；升级请将BDA与两个资源包一起安装。

## 河流轮廓与原始像素

alpha.4的资源004图块16～40、42～45共29帧使用`original-river-plane`规则。此前生成图虽保留16×16尺寸，但部分转角被圆化，T27等图块多出中间岸线，原水纹也被放大、移位。仅核对尺寸或水面颜色不足以保证相邻图块能拼接。

[river-geometry.json](terrain/river-geometry.json)是当前水域素材的可编辑定义：保存原PNG哈希、每帧河岸方向/外侧陆地角和五种颜色。颜色取自此前GPT Image图集的明确像素，已有彩色PNG及母图保留作调色参考。打包时`tools/river_geometry.py`直接解码原始16×16四灰度平面：0为深岸线、85为岸边阴影、170为水纹、255为水或河岸外侧陆地。所有非白像素保持原坐标；不经过插值缩放，不修改原库、地图矩阵或游戏代码。

这29帧的`catalog.json.geometry`决定最终CLR像素；对应`library/`彩色PNG不是其最终形状来源。修改水域颜色应编辑上述定义的`palette_rgb`，而不是移动PNG里的岸线。普通构建直接读取定义；仅在重新核对原图及调色来源后运行`python tools/river_geometry.py`刷新定义。

```powershell
python tools/color_assets.py build
python tools/test_river_geometry.py
```

新增检查直接以原LIB的2bpp字节为依据，验证1263个岸线像素和656个水纹像素位置，以及29帧真实MIPS绘制/裁切；还拼接七张原战场地图、覆盖2039个水域格和117种实际邻接组合。最终地图预览生成到`build/river-geometry/`。模拟器验证范围见根目录验证记录。

照片区域的[轮廓对照图](../../docs/screenshots/river/photo-map-113-comparison.png)从左到右是原始灰度资源拼图、alpha.3彩色PNG拼图、alpha.4最终CLR解码像素，均为资源113的(0,6)视口；这是资源对照图。实际模拟器截图和像素验证另见`docs/screenshots/color/river-map-*.png`及`river-atlas.png`。
