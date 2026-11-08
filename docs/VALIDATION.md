# 验证记录

当前彩色BDA：214700字节，SHA-256 `5193aaf0db29ca7eeef367456541bfa39781c36c9f4849fb116d97245b1c59a0`。
LIB：461116字节，SHA-256 `01869a536d248156beef8d00c8185b5670731df82fbed39e9daba46fec8b2a11`。
CLR：2282488字节，SHA-256 `ed6a96a375249e4a0b104301c7ed35ca5d819f467d0e826814ababbaa0e39ca4`。
固定SDK `ef3bf3b7328a3a8fa9ba48593c63285300725fb7`，GCC15.2.0。

## 本轮已完成

| 检查 | 通过数 | 实际范围 |
| --- | ---: | --- |
| 彩色生产MIPS | 3818 | 全1204帧的原偏移查找、PNG/RGB565字节、尺寸及mask类型；140张战斗精灵逐像素；原遮罩、裁切、屏幕/上下文、补充底栏/制作群组；真实CRC/解析/SDK文件生命周期、缺包/损坏包/分配失败/清理 |
| 既有MIPS回归 | 1167 | 593既有回归、58底栏/天气/文字/触摸、9摘要、507实际地图可视区；使用灰度兼容配置，原机器码对照单独禁用可选彩色加载，加载和RGB路径由上一行实际执行 |
| 生产MIPS新旧对照 | 27163 | 与上轮b37442d确切ELF比较地图/战斗输入、数值、列表、动画时间轴、搜索、计谋、出征和软浮点；绘制/模态边界建模 |
| 原生C200彩色界面 | 14 | 主菜单、全76800像素制作群组、战略地图/头像、底栏8640像素、战斗状态行/天气/摘要、天数1/10居中、信息/查找及返回和移动 |
| 资源回包 | 10 | 87原条目及空槽保留、原库逐字节还原、89条扩展库往返、遮罩/行填充/动画/地图/尺寸/索引约束 |
| 扩展LIB加载模型 | 4 | 实际生产MIPS完整分配和读入461116字节，定位17/18/33资源 |
| 源码结构 | 42模块/446恢复函数 | 独立编译、函数索引和89项代码用途依据检查 |

彩色及既有MIPS共4985项，均0失败。全部1204帧已上色，重复帧共用654份RGB像素，18张选用GPT Image母图及提示词随仓库保存。
原LIB、动画指令、45536字节初始化数据逐字节保持一致；战斗/战略/存档源码和状态布局与b37442d不变。
当前BDA和CLR已分别重建并得到相同SHA-256。新增RGB缓存约2.18MiB，独立于原存档状态区。

汇总：[color-resource-validation.json](../validation/color-resource-validation.json)。
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
python tools/test_battle_hud.py
python tools/test_battle_summary.py
python tools/test_battle_viewport.py
python tools/package_release.py --require-validated
python tools/verify_artifacts.py --require-validated
python tools/test_release_pipeline.py
```

新旧逻辑对照另需保留上轮ELF：`python tools/test_control_flow.py --baseline PATH/TO/previous/sango.elf`。
CI执行资源/源码检查、编译、彩色及三项战场MIPS检查、打包和完整性检查；不运行私有固件。

## 原生证据的范围

截图位于 [docs/screenshots/color](screenshots/color/)，README展示同一次运行的菜单、战略、战斗、天数和制作群组。
原生检查使用本地C200固件、QEMU bbk9588/24Kf和硬件输入字符设备。合成NAND的ECC读取存在差异，
因此在正常入口/加载点装入准确BDA、扩展LIB和CLR；单独RAM启动夹具执行生产CRC/索引解析，再回正常片头/菜单。
战场由另一个只用于验证的RAM夹具准备地形和摘要状态，绘制、原生字体、触摸和输入处理仍执行生产代码。
这些夹具没有编入交付BDA；[装载记录](../validation/color-native-staging.json)给出准确文件和夹具哈希。
SDK文件加载、分配失败和资源释放由编译MIPS模型另测，不将RAM装载证据声称为原生文件系统或真机验证。

这14项替代当前发行参考中的旧版27项灰度固件检查；旧报告仍按其中BDA哈希及历史提交追溯。
当前全彩BDA未完成真机、完整战斗/AI/战役、完整原生存读档、长按和全部触摸合成ESC分支验证。
不把旧版本的设备反馈计为本版真机通过。

## 历史阶段

前一版未压扁底栏的BDA是 `8593e3…`，见 [battle-toolbar-aspect-validation.json](../validation/battle-toolbar-aspect-validation.json)，源码快照b37442d。
更早的布局、底部摘要、可读性重构和原库解包证据分别保留在各历史摘要及对应提交中。
恢复446个函数、42模块和语义名称的过程见 [源码导航](SOURCE_GUIDE.md)、[复杂函数整理](CONTROL_FLOW_REFACTOR.md)、[短函数整理](IDENTIFIER_CLEANUP.md)。
60026项独立运行库对照属于历史未改运行库证据，未计为本轮新跑结果。

素材命名仍依据 [实际代码用途](../assets/library/代码用途核对.md) 和选择表；012/060/074保留未定位当前调用的边界。
CLR格式、语义素材及编辑流程见 [彩色资源说明](../assets/color/README.md)。
