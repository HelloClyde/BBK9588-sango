# 验证记录

当前彩色BDA：214700字节，SHA-256 `25c531c9cd78c65bf226a761fa25f24c50e2f364bc566cd670c65d49e2b50fe2`。
LIB：461116字节，SHA-256 `01869a536d248156beef8d00c8185b5670731df82fbed39e9daba46fec8b2a11`。
CLR：2294040字节，SHA-256 `055b422e7c845bea94f0d634f967a59a9fe8031f7c66dd3465a174a7c98b72ce`。
固定SDK `ef3bf3b7328a3a8fa9ba48593c63285300725fb7`，GCC15.2.0。

## 本轮已完成

| 检查 | 通过数 | 实际范围 |
| --- | ---: | --- |
| 彩色生产MIPS | 3818 | 全1204帧的原偏移查找、PNG/RGB565字节、尺寸及mask类型；140张战斗精灵逐像素；原遮罩、裁切、屏幕/上下文、补充底栏/制作群组；真实CRC/解析/SDK文件生命周期、缺包/损坏包/分配失败/清理 |
| 既有MIPS回归 | 1167 | 593既有回归、58底栏/天气/文字/触摸、9摘要、507实际地图可视区；使用灰度兼容配置，原机器码对照单独禁用可选彩色加载，加载和RGB路径由上一行实际执行 |
| 历史生产MIPS新旧对照（e3cadec） | 27163 | 与上轮58afd1a确切ELF比较地图/战斗输入、数值、列表、动画时间轴、搜索、计谋、出征和软浮点；绘制/模态边界建模 |
| 战斗彩色/背景恢复 | 250 | 实际地形分类、168帧原遮罩核对、天气/数字透明、17组真实时间轴、背景恢复/裁切/中断/分配失败和末帧保留 |
| 最终像素网格 | 21 | 6张单比特字形按1:1烘焙，真实MIPS完整5760像素复制、局部恢复、尾部CRC/边界及旧文件兼容 |
| 图片底栏与居中 | 113 | 原图片底色恢复、数字/姓名透明、8类地形与姓名单行切换、30种计谋和36种普通攻击坐标/状态对照 |
| 战略地图/选择箭头 | 88 | 10帧城市透明键和封闭白色细节；18个视口；完整240×232像素覆盖；四向重画；选择箭头68像素及49格完整轮廓/透明背景；作用域与灰度回退 |
| 原生C200彩色界面 | 30 | 主菜单、全76800像素制作群组、战略地图/头像、底栏8640像素、战斗状态行/天气/摘要、天数1/10居中、信息/查找及返回和移动；选择箭头原轮廓、下移、背景恢复和返回 |
| 资源回包 | 10 | 87原条目及空槽保留、原库逐字节还原、89条扩展库往返、遮罩/行填充/动画/地图/尺寸/索引约束 |
| 扩展LIB加载模型 | 4 | 实际生产MIPS完整分配和读入461116字节，定位17/18/33资源 |
| 源码结构 | 42模块/446恢复函数 | 独立编译、函数索引和89项代码用途依据检查 |

彩色及既有MIPS共5457项，均0失败。全部1204帧已上色，重复帧共用654份RGB像素，22张图形美术母图及提示词随仓库保存。
原LIB、动画指令和45536字节初始化数据逐字节保持一致。战略绘图函数增加彩色视口映射，其城市选择、滚动和存档规则不变；战斗底栏保持原比例。
当前BDA和CLR已分别重建并得到相同SHA-256。新增RGB缓存约2.18MiB，独立于原存档状态区。

前轮箭头修复：[city-cursor-validation.json](../validation/city-cursor-validation.json)；前轮地图修复：[strategy-transparency-validation.json](../validation/strategy-transparency-validation.json)，地图专项：[strategy-color-validation.json](../validation/strategy-color-validation.json)。
上一轮全彩更新汇总：[color-resource-validation.json](../validation/color-resource-validation.json)，按其中snapshot_commit追溯。
原始报告：[彩色MIPS](../validation/color-mips-validation.json)、[固件界面](../validation/color-firmware-validation.json)、[新旧逻辑](../validation/control-flow-validation.json)。
`reference-build.json`用于发行包的BDA/LIB/CLR三份独立校验，升级ZIP及外部文件均有逐文件SHA-256。

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
python tools/test_battle_ui_color.py
python tools/test_battle_pixel_grid.py
python tools/test_battle_hud.py
python tools/test_battle_summary.py
python tools/test_battle_viewport.py
python tools/package_release.py --require-validated
python tools/verify_artifacts.py --require-validated
python tools/test_release_pipeline.py
```

新旧逻辑对照另需保留上轮58afd1a的ELF：`python tools/test_control_flow.py --baseline PATH/TO/previous/sango.elf`。
CI执行资源/源码检查、编译、彩色及五项战场MIPS检查、打包和完整性检查；不运行私有固件。

## 原生证据的范围

截图位于 [docs/screenshots/color](screenshots/color/)，README展示同一次运行的菜单、战略、战斗、天数和制作群组。
原生检查使用本地C200固件、QEMU bbk9588/24Kf和硬件输入字符设备。合成NAND的ECC读取存在差异，
因此在正常入口/加载点装入准确BDA、扩展LIB和CLR；单独RAM启动夹具执行生产CRC/索引解析，再回正常片头/菜单。
战场由另一个只用于验证的RAM夹具准备双方20支部队、地形和摘要状态，绘制、原生字体、触摸和输入处理仍执行生产代码。
这些夹具没有编入交付BDA；[装载记录](../validation/color-native-staging.json)给出准确文件和夹具哈希。
SDK文件加载、分配失败和资源释放由编译MIPS模型另测，不将RAM装载证据声称为原生文件系统或真机验证。

这30项包含既有29项界面检查，并验证6个固定字形的每个前景像素严格落在原生LCD网格。状态图及按钮图按1:1复制，四段演出框/时间轴保持居中。旧版27项灰度固件报告按其中BDA哈希及历史提交追溯。
当前全彩BDA未完成真机、完整战斗/AI/战役、完整原生存读档、长按和全部触摸合成ESC分支验证。
不把旧版本的设备反馈计为本版真机通过。

## 历史阶段

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
