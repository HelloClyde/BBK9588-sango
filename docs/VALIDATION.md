# 验证记录

## 当前开发版 alpha.8

当前BDA为239476字节，SHA-256 `16db08f6275f63f8c6c95c2e7b9b934dc8c3105afeff257a5025151f691fb0c9`；LIB为518848字节，SHA-256 `a95106b2d658ee4c45c4051f7e5d67d7eb3aab5cdb1a4d8cdb921978ccafb18c`；CLR为2759168字节，SHA-256 `4c8c66674e6b5c4d924b0c68c78f966d89ec3e06e79f33775d0cc14246ce831e`。

本轮修改势力页绘制路径，复用游戏/辅助画布，以SDK原尺寸RGB565整块绘制图片，首次完整组页后才提交；切换仅提交局部，城市闪烁也在同一地图事务内完成。没有修改素材、游戏规则、存档格式或初始化数据。LIB、CLR及三首音乐与前次白边修复逐字节一致。

当前确切BDA通过4550项编译MIPS/主机检查：设置32、彩色3926、音乐65、存档104、菜单44、触摸132、开门41、势力页138、菜单透明34、势力响应34。另有2项旧版问题重现不计入总数。原87条资源和45536字节初始化数据保持原字节，93项资源语义核对通过。逐项报告见 `validation/alpha8-*-validation.json` 与 [当前参考](../validation/reference-build.json)。

21项原生C200检查覆盖四剧本姓名/头像、底图、触摸预览与确定/返回、快速按键滚动及首次页面检查后立即发送80ms触摸。观察到首个预览在1秒内完成；截图采样耗时约0.266秒包含手势、模拟器和HTTP开销，不是硬件测时。工作量检查确认相邻切换的窗口更新为13117像素，非76800像素整屏；不作真机帧率声明。方法、截图、哈希见 [势力页](RULER_SELECTION.md)、[MIPS响应记录](../validation/ruler-response-validation.json)和 [原生响应记录](../validation/ruler-response-firmware-validation.json)。

固件验证使用独立合成NAND和精确字节RAM装载，不表示原生文件系统、真机音量/性能或完整战役通过。此前19项设置页与10项菜单原生报告保留旧BDA哈希，没有计为本轮结果。固定SDK仍为 `ef3bf3b7328a3a8fa9ba48593c63285300725fb7`，GCC15.2.0。

## alpha.7历史记录

BDA：234712字节，SHA-256 `c6531141225c27bb5b9de66af004b9b07697a38e156f8eaafbe4bd473ec19b47`。

LIB：499630字节，SHA-256 `b99b32769a0144262e7af79bfa9605cdcafafcc55db23b3071fa9a226179e0d3`。

CLR：2605552字节，SHA-256 `117c6e723d1b88311438c6a4d05825f45c8abc63181ad9bc79c887422250a1df`。

固定SDK `ef3bf3b7328a3a8fa9ba48593c63285300725fb7`，GCC15.2.0。原87条资源与45536字节初始化数据保持原字节；木质UI和势力预览使彩色帧数增至1239，独立像素组689。三首音乐字节保持alpha.6版本。

| 当前编译MIPS检查 | 通过数 |
| --- | ---: |
| 彩色索引、PNG/RGB565、CRC、遮罩与加载 | 3923 |
| 战略地图、战斗彩色、河流与字形网格 | 448 |
| 触摸、信息/天气、战斗选项 | 185 |
| 音乐解码、反压、切歌和退出 | 65 |
| 存档布局、菜单绘制、开门动画、势力预览 | 327 |
| 战斗图片底栏、状态栏、摘要和视口 | 688 |
| 合计 | 5636 |

以上为无需本地旧程序即可执行的检查；本地另有2项旧诊断版问题重现，不计入5636。实际代码在MIPS中执行，SDK绘制/输入/文件/音频边界按各报告建模。逐项报告为 `validation/alpha7-*-validation.json`，入口与计数见 [当前参考](../validation/reference-build.json)。另有10项资源回包检查，以及42模块/446恢复函数和92项资源用途核对。

本轮确切BDA、LIB、CLR完成20项原生C200固件势力页检查，覆盖四剧本头像和背景逐像素、原生字体、触摸预览/滚动/确定/返回和键盘。报告与截图哈希见 [原生势力页](../validation/ruler-ui-validation.json)。使用独立NAND、受控入口及精确字节RAM装载，隔离合成NAND的ECC差异，不代表原生文件系统或完整战役通过。Actions只执行源码构建、MIPS检查及打包。

存档、弹出菜单、木色UI与开门动画的原生截图分别在对应文档中；这些阶段的报告保留其历史BDA哈希，没有计为当前20项原生检查。开门动画为项目新增，不宣称与全部9288S版本逐帧一致。

用户确认D1诊断版真机已出声，随后反馈卡顿。本版设置播放电平并恢复原设置、增加4KiB预读、限制每次提交1024字节PCM；最新整包的真机音乐流畅度仍待复验。交付版无诊断日志。见 [音乐改进](MUSIC_PLAYBACK.md)。

独立干净检出构建及安装包校验见 [干净构建](../validation/release-clean-build.json)。新UI/音乐状态位于原固定状态区之外，链接器上限为0x81c34000；存档格式和原初始化数据不变。升级需同步替换BDA、LIB、CLR，完整ZIP附三首音乐及逐文件SHA-256。

## alpha.6及更早的历史记录

下文保留历史构建及验证方法；其中“当前”“本轮”均指对应历史快照。

当前音乐版BDA：227196字节，SHA-256 `c5149aab1220dacff32377b93e7f8864670a424f55aeab21b5033d09ee72489d`。
LIB：461116字节，SHA-256 `01869a536d248156beef8d00c8185b5670731df82fbed39e9daba46fec8b2a11`。
CLR：2297312字节，SHA-256 `77c1b58d85d95765be331a5d91c61d0a6545ee39a6712b05d09916cb2f8dd793`。
固定SDK `ef3bf3b7328a3a8fa9ba48593c63285300725fb7`，GCC15.2.0。

## 当前执行文件的检查

| 检查 | 通过数 | 实际范围 |
| --- | ---: | --- |
| 彩色生产MIPS | 3818 | 全1204帧索引、PNG/RGB565字节、尺寸与遮罩；真实CRC、解析、文件生命周期、缺包/损坏/分配失败；140张战斗精灵逐像素 |
| 战略地图/选择箭头 | 88 | 城市透明、18个视口、240×232覆盖、四向重画、68像素箭头与49格完整轮廓 |
| 战斗彩色/背景恢复 | 250 | 地形分类、168帧遮罩、天气/数字透明、17组真实时间轴、恢复/裁切/中断/失败 |
| 图片底栏与居中 | 113 | 原图底色、透明文字、姓名/地形单行切换、30种计谋与36种攻击坐标/状态 |
| 最终像素网格 | 22 | 七张16×16单比特字形1:1烘焙；真实MIPS完整5760像素复制、恢复、CRC/边界和旧文件兼容 |
| 战斗底栏、摘要、可视区 | 575 | 分别59、9、507项；保留布局、天气、底部摘要、15×13绘制、滚动/边界/覆盖层 |
| 信息页与天气MIPS | 27 | 真实信息页字段、16像素排版、GBK换行、极值/无效值、分配失败/释放、战斗计算视图恢复；天气18×18透明复制、源索引/CRC/边界及卸载 |
| 新增触摸MIPS | 132 | 原生窗口回调、完整16位坐标、按下/抬起/取消、8像素阈值、重复释放、SDK采样定时器、菜单、列表、存档槽、数值、城池与三种战斗选择模式、拖动、边界及边缘轻点不滚动 |
| 河流原始轮廓MIPS | 88 | 29帧1263个岸线、656个水纹像素直接对比原LIB；七地图2039个水域格和117种邻接；87项真实绘制/裁切加照片对应完整视口 |
| 原生C200彩色界面 | 61 | 七地图21个视口、29帧原生图集； 同y=232处的两栏全部8640像素一致；菜单/制作群组、战略地图/箭头、战场/透明文字/信息/查找、天数居中、背景恢复和四段真实动画 |
| 战斗选项MIPS | 26 | 真实文本解码和选择器；五行映射、两值/取消、触摸/实体键及连续操作；旧ELF另重现两处错误 |
| 原生C200触摸流程 | 33 | 全部五项战斗菜单、三项设置和撤退返回值； 菜单→剧本→君主→正常开局；武将→合法目的地→攻击菜单→目标；数值修改/确认、战略横纵拖动与上下边界、战斗三种选择状态拖动/反向恢复/松手不确认、边缘轻点不滚动、触摸后实体键、城池ID |
| 背景音乐MIPS | 63 | 三首全部样本与独立FFmpeg解码SHA校验；24块真实MIPS解码及播放器场景、循环、短读短写、反压、损坏、退出、定时器输入隔离 |
| 原生C200背景音乐 | 6 | 真实播放器/解码与SDK音频、计时和窗口定时器；压缩文件从校验过的RAM文件边界读取以隔离合成NAND错误；音频数据包采样对比及关闭清理 |
| 资源回包 | 10 | 原87条/空槽保留、原库逐字节还原、89条扩展库往返、遮罩/行填充/动画/地图/索引约束 |
| 源码结构 | 42模块/446恢复函数 | 模块独立编译、函数索引、89项资源用途依据；新增触摸模块独立于恢复模块 |

当前确切BDA新跑5202项编译MIPS检查及100项原生固件检查，均0失败。前轮15857项按键对照属于alpha.1的14行视口，不计为本轮新跑结果；当前卷动状态会按13行显示区有意变化。
此前593项既有回归、27163项控制流对照及60026项运行库对照保留为历史证据，没有计为本轮新跑检查。
本轮新增独立音乐模块和场景、输入/绘图泵接入；LIB和CLR与alpha.5完全一致，图像素材不变。45536字节初始化数据的SHA-256仍为 `970e2121b60aa27d340563a249d63df2c67ce7a006ee8cb4c6cddd0cf0f3301f`，原存档布局未改。
新增触摸、信息页和音乐代码/状态位于原固定状态区之后的受限区间，链接器检查其末端不超过0x81c30000。
alpha.1把战斗光标闪烁计数器从未初始化改为0；该轮历史按键对照排除这一绘制相位/次数差异，比较游戏决策、状态、命令及输入消耗。

本轮汇总及源码/报告哈希见[背景音乐验证](../validation/music-review.json)、[音乐MIPS](../validation/music-validation.json)和[音乐原生输出](../validation/music-native-validation.json)。

前轮战斗菜单修复记录按alpha.5快照追溯：[战斗菜单修复记录](../validation/battle-options-review.json)，[9288S/9588静态对照](../validation/battle-options-reference.json)与[具体菜单语义](BATTLE_OPTIONS.md)。前轮河流、信息页记录按alpha.4/alpha.3快照追溯。原始报告：[触摸MIPS](../validation/touch-input-validation.json)、[按键对照](../validation/touch-keyboard-validation.json)、[触摸固件](../validation/touch-firmware-validation.json)、[彩色MIPS](../validation/color-mips-validation.json)、[彩色固件](../validation/color-firmware-validation.json)。
问号按16×16单比特字形烘焙，天气按原生18×18绘制；信息页后台一次画完整页并提交，保持到点击或按键返回。新信息页不进入逐行直接绘屏路径，临时攻防计算视图读出后恢复，原游戏状态与战场缓冲不改。
独立干净检出构建及安装包检查见 [干净构建记录](../validation/release-clean-build.json)。
发行包由 `reference-build.json` 分别校验BDA/LIB/CLR和三首音乐；升级ZIP和外部文件均有逐文件SHA-256。

沿用alpha.2按钮栏y=232、高36，与战略界面一致；粮草／天气行y=208，摘要y=268。原六张字形及1204帧图片未改，新增问号字形和五张原生天气图，战场显示区保持15×13；移动/AI/技能的15×15规则窗口不变。

## 音乐验证范围

三首完整曲目共11,509,218个样本，主机逐样本解码SHA与转换时保存的独立FFmpeg结果一致；24个选定块同时执行真实MIPS解码。
真实播放器在MIPS中检查逐曲切换、精确曲尾与跨块循环、部分读写、队列反压、失败静音和退出。生产入口分别覆盖主菜单、战略、玩家战斗和电脑自动战斗。

C200原生检查执行同一播放器、解码器和真实SDK音频/时间/定时器。原生SDK读取合成NAND时已测得音乐头/数据与原文件不同，因此原生播放检查将四个命名文件边界换为校验过的RAM文件；这项诊断适配不进入BDA，也不宣称原生文件播放全链路通过。
本地旧Python前端未接收新版QEMU的PCM数据包，验证适配器只补充接收和记录，不修改SDK音频。音频采样与已知解码样本对照；具体变换和采样位置在原生报告中列明。
真机音质、持续播放性能和完整战役仍需实际设备确认。

## 触摸范围与限制

[触摸操作](TOUCH_CONTROLS.md)列出菜单、城池、人物、移动/攻击目标、信息/查找、列表、数值和存档槽的具体操作。
按下/抬起使用SDK窗口消息，坐标使用命名SDK接口；独立20ms定时器不推进游戏时钟，不混用全局原始输入队列或直接访问GUI指针。
轻点在抬笔时触发一次，拖动不会确认人物或命令；长按地图不确认；实体按键取消尚未释放的触摸。

连续拖动已在C200模拟器通过：SDK坐标在按住期间持续更新，战略地图横向/纵向滚动及上下边界、战斗三种选择模式滚动/反向恢复、松手不确认均有原生轨迹证据。此前只发三个大幅跳点的诊断没有覆盖真实连续手势，已被本轮测试替代，不再据此判断SDK不支持拖动。

地图视野统一由拖动移动，空地轻点仅移动光标，边缘轻点不再滚动。轨迹见 [touch-drag-trajectories.json](../validation/touch-drag-trajectories.json)。真机仍未验证。

## 如何复验

```powershell
python -m pip install -r requirements-assets.txt -r requirements-validation.txt
python build.py --cc PATH/TO/mipsel-none-elf-gcc.exe
python tools/source_index.py --check
python tools/audit_resource_usage.py --check
python tools/test_sango_lib.py
python tools/test_color_assets.py
python tools/test_strategy_color_map.py
python tools/test_battle_color.py
python tools/test_river_geometry.py
python tools/test_battle_ui_color.py
python tools/test_battle_pixel_grid.py
python tools/test_battle_hud.py
python tools/test_battle_summary.py
python tools/test_battle_viewport.py
python tools/test_touch_input.py
python tools/test_battle_info.py
python tools/test_battle_options.py
python tools/test_music.py
python tools/package_release.py --require-validated
python tools/verify_artifacts.py --require-validated
python tools/test_release_pipeline.py
```

alpha.1的15857项历史按键对照见 [原报告](../validation/touch-keyboard-validation.json)，对应快照4d2b589。本版显示区从14行改为13行，未把旧几何状态的相等性声称为新跑结果。
CI执行源码/资源检查、编译、彩色/战场/触摸MIPS、打包和完整性检查；不运行私有固件，也不下载历史ELF进行按键对照。

## 原生证据的范围

彩色截图位于 [screenshots/color](screenshots/color/)，新增触摸流程截图位于 [screenshots/touch](screenshots/touch/)。
检查使用本地C200固件、QEMU bbk9588/24Kf和硬件输入字符设备。合成NAND存在ECC差异，因此在正常入口/加载点装入准确BDA、LIB及CLR；RAM启动夹具执行生产CRC/索引解析，再回正常片头/菜单。
战场夹具准备双方20支部队、地形和摘要状态；触摸夹具依次调用生产人物、移动、指令、目标、数值及城池选择控制器，标记仅记录返回值。正常开局另走真实主菜单、剧本、君主和会话流程。
绘制、原生字体、窗口消息及触摸/按键处理均执行生产代码。夹具没有编入交付BDA；[彩色装载记录](../validation/color-native-staging.json)与[触摸装载记录](../validation/touch-native-staging.json)给出准确载荷、资源及夹具哈希。
SDK文件加载、分配失败与资源释放由编译MIPS模型另测；未将RAM装载声称为原生文件系统或真机验证。

本版未系统验证真机、完整战斗/AI/战役或完整原生存读档。旧版本设备反馈不计为本版通过。

本轮河流检查以原LIB的2bpp字节为轮廓依据，逐坐标核对0/85岸线与170水纹；显式河岸方向/陆地角规则是经原图核对的元数据。照片区域对应资源113、视口(0,6)，22个山地/树林/营寨位置一致，完整240×208绘制经真实MIPS对比。原生另外比较七地图21个视口及29张水域图块的全部像素。更早仅检查尺寸与蓝色像素数，不能证明上色没有改变岸线，已由新增检查补齐。

本轮对照原始9288S EXE静态代码及两版资源001文字，确认9588原版将“敌军移动”和“全军撤退”分支接反；恢复C此前保留了该移植错误。26项真实MIPS菜单检查和8项新增原生断言验证了五行、设置、取消及返回值。原始9288S对照为静态证据，不计作本轮9288S运行验证；新原生操作在9588/C200完成。

## 历史阶段

alpha.4（1cf768d）的河流轮廓与86项原生验证记录保留在[river-geometry-review.json](../validation/river-geometry-review.json)，报告哈希按该提交追溯。

alpha.3（71a2d93）的问号、天气与信息页记录保留在[battle-hud-info-sharp.json](../validation/battle-hud-info-sharp.json)，报告哈希按该提交追溯。


前一版未压扁底栏的BDA是 `8593e3…`，见 [battle-toolbar-aspect-validation.json](../validation/battle-toolbar-aspect-validation.json)，源码快照b37442d。
更早的布局、底部摘要、可读性重构和原库解包证据分别保留在各历史摘要及对应提交中。
恢复446个函数、42模块和语义名称的过程见 [源码导航](SOURCE_GUIDE.md)、[复杂函数整理](CONTROL_FLOW_REFACTOR.md)、[短函数整理](IDENTIFIER_CLEANUP.md)。
60026项独立运行库对照属于历史未改运行库证据，未计为本轮新跑结果。

素材命名仍依据 [实际代码用途](../assets/library/代码用途核对.md) 和选择表；012/060/074保留未定位当前调用的边界。
CLR格式、语义素材及编辑流程见 [彩色资源说明](../assets/color/README.md)。

当前选择箭头已按原颜色平面恢复完整向上轮廓，以独立透明键替换损坏的旧遮罩；68个箭头像素全部保留，79个旧白底像素不再覆盖地图。49个格子及原生移动/返回均已验证。此前箭头修复记录按2502778历史提交追溯。

前轮战斗彩色修复（40443c6）见 [battle-color-review.json](../validation/battle-color-review.json)：46帧地形按代码分类补齐底色和蓝色水域，天气与伤害数字去除白色底，过期动画精灵经SDK恢复原底图。原LIB、指令、游戏规则与存档区不变。原生四段动画及黑白像素背景恢复通过，截图/动画位于docs/screenshots/color。

前轮图片底栏修复（7ef3ff1）见 [battle-hud-image-validation.json](../validation/battle-hud-image-validation.json)：固定标签仍来自图片素材，选用常规笔画而非粗体；动态文字透明且更新时局部恢复原底图。右侧沿用原版的姓名/地形单行切换；绿色树林和130×64演出框居中已验证。SDK接口、动画指令、游戏规则及存档布局不变，字体像素与完整战役的验证范围详见报告。

本轮像素网格修复见 [battle-pixel-grid-review.json](../validation/battle-pixel-grid-review.json)：GPT Image保留美术底图，6张16×16单比特点阵在导出最终PNG时以整数坐标烘焙；状态图240×24、按钮图240×36在设备上按1:1贴图。原1204条索引与LIB不变，CLR另含经CRC/边界检查的原生状态图。字体文件不随包分发，正常构建不依赖字体安装。



上一轮（2739e71）启动图标按用户确认的原图构图恢复：曹操在左下角，没有金冠；身后整面旗帜铺满背景，旗上只露出部分“曹”字。去除误加的独立小旗、云纹及回纹，并按用户圈选去掉右侧孤立黑色笔画，恢复连续旗布；原图参考和未采用草稿均保留。四种SDK VX图标像素/尺寸、BDA静态校验和完整程序载荷一致性共6项通过。该轮与4b5e97a相比，仅图标和容器校验改变，执行载荷、ELF、LIB、CLR逐字节一致；5457项MIPS及30项原生游戏界面证据沿用该相同载荷，本次未重新跑完整游戏检查或真机启动器检查。见 [图标记录](../validation/app-icon-validation.json)。

前轮（2519f33）状态图微调：“粮”由x=2移至4，“天”由x=80移至82，各向右2个原生像素。字形、背景和按钮不变，粮草数字仍从x=21开始，间隔2列像素。3818项彩色、113项底栏/演出、21项像素网格检查及30项原生C200界面检查重新通过；其余1505项MIPS检查沿用相同执行载荷和索引素材的证据。详见 [位置记录](../validation/battle-label-position.json)。

前轮（19d7ea3）UI采用用户确认的金色方案：金色边框、浅金纸底、深金/铜色纹饰，覆盖主菜单、剧本、存读档、制作群组及战斗/地图共用底栏。原红绿母图、提示词和目标PNG保存在 `assets/color/variants/red-green-ui/`。这是一种上色选择，不代表已证实的9288S历史配色。固定字形/坐标、BDA执行载荷、ELF和LIB不变，仅5帧UI及原生状态图更新，其余1199帧PNG不变。3952项相关MIPS及30项原生C200界面检查重新通过，详见 [金色UI记录](../validation/gold-ui-validation.json)。

前轮（01a990f）菜单/底栏去除母图中放大的像素块与颗粒纹理，改为连续金色纹饰和细腻明暗；实际输出尺寸保持240×320、240×24及240×36，固定标签仍以1:1点阵显示。原金色颗粒版母图、提示词和原生PNG保存在 `assets/color/variants/gold-pixel-ui/`。仅5帧UI及原生状态图改变，头像、城市、战斗人物/地形等其余1199帧未改；设备像素上限仍存在。3952项相关MIPS和30项原生C200界面检查通过，详见 [UI细化记录](../validation/smooth-ui-validation.json)。
