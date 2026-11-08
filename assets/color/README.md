# 游戏内彩色素材

1204帧均有彩色PNG：原库1202帧及补充底栏、竖屏制作群组2帧。原RGBA图案去重后为654种，分18张图集通过GPT Image上色，再按原坐标裁切到原生尺寸。原始灰度素材和 `../drafts/color9288s/` 三张既有草稿保留。

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

编译MIPS检查覆盖全部1204帧查找、RGB565字节、140张战斗精灵的原遮罩、屏幕/上下文绘制、裁切、缺包和损坏包、分配失败及文件清理。固件界面范围见根目录验证记录。

## sango.clr 格式和加载

`build/sango.lib` 仍保留全部原资源、透明遮罩和动画时间轴，字节不因上色变化。CLR必须与它一起安装到 `应用/数据/游戏/`。BDA通过SDK命名接口读取同目录的CLR并绘制RGB565，不写GUI表或直接操作帧缓冲。缓存独立于旧存档区，约2.18MiB；缺包、错误大小/索引、LIB大小或CRC32不匹配、内存不足时回退原灰度路径。

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

每个16字节索引项是 `<IIHHI>`：原LIB帧像素偏移、CLR像素偏移、宽、高、原flags；按原LIB偏移严格递增。像素是逐行RGB565、每像素2字节，完全相同的帧共享像素区。flags低位保留原flags，mask位继续读取原LIB的2bpp透明遮罩；新增0x100位表示RGB565的0值为透明像素，不写入目标。带此位的帧将不透明纯黑编码为0x0001，避免混淆。原有RGBA遮罩仍以原LIB为准。资源055原本没有透明遮罩，彩色版在catalog中另声明edge-connected-white：只将与边缘连通的近白背景编码为透明键，保留封闭的白色窗户/屋顶细节。原PNG及原LIB不变。原生上下文复制使用0作为透明键，因此不透明纯黑通过SDK助手转换为0x0001。

来源和许可边界见 [声明](../../THIRD_PARTY_NOTICES.md)。
