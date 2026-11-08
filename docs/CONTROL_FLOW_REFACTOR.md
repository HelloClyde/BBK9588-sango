# 复杂函数整理与行为对照

本页为历史重构阶段记录；后续战斗底栏修复已改变BDA，最新结果见 [验证记录](VALIDATION.md)。

本页记录第二阶段控制流整理。第三阶段已继续整理剩余短函数的变量和标签，
该阶段保持本页生产镜像字节不变，见 [短函数命名整理](IDENTIFIER_CLEANUP.md)。

本轮相对 `ad129c18bdb7a7b254b739a58fb046a9e9713b7d` 整理95个函数。
按函数统计，原样式的临时标识符从2616个减少到1509个，`goto` 从244处减少到131处。
这包含删除无用临时值和拆分重复使用的变量，不等于新增了1107个独立状态字段。
所有90行及以上函数已不含 `uVar`、`iVar`、`param_N` 等原样式临时名。

| 流程 | 主要整理 | 保留的行为约定 |
| --- | --- | --- |
| 战略与战场输入 | 输入循环、方向分支、触摸、查找图关闭、重绘 | 关闭查找图会消费该次输入；坐标按原宽度回绕 |
| 武将/宝物列表、数值输入 | 分页、选中行、重绘标志和数字位编辑 | 原分页边界、末页填充判断和数值掩码 |
| 计谋与动画 | 使用者/目标、命中值、效果量、资源/指令索引、延迟和存活计数分开 | 失败仍扣技力；原随机顺序、零延迟/相邻延迟、连续消息栈区 |
| 出征与搜索 | 势力归属与排序索引分开；发现人物、宝物、粮钱分支明确 | 名册与归属的0/1基约定；空城、同势力入城及原排序细节 |
| 运输、外交、AI、月度事件 | 阶段、选择、花费、名册和事件标签命名 | 菜单回退、原决策条件、原月度索引与整数截断 |
| 绘图、格式化、软浮点 | 坐标/裁剪/扫描变量、格式解析/转换/输出、浮点分类/指数/尾数分开 | 原像素布局、CRLF、补零、`%n`、O32对齐及浮点舍入 |

没有把全部跳转机械删除：共享释放、运输向导回退、公共输出收尾继续使用有含义的标签。
没有顺手修正原程序的特殊或可疑规则。战场输入中恢复出的未初始化计时值保持原状，
对照包含多种调用寄存器初值；这不构成对任意未定义行为的完整证明。

代码核对还更正了两处误名：`sango_raster_invert_packed_rectangle` 实际反转帧缓冲矩形；
`sango_item_mark_discovered` 设置宝物名册的已发现位。格式化入口也不再误称为只处理整数。
新旧函数与局部名的追溯仍保存在 `source-map.json`，资源89项用途依据和函数索引已同步。

## 验证结果

生产 BDA 为214700字节，SHA-256：
`3f193d6e2f9a345b55f595ad7dbb93f4173dbc938088b42b744b5a6362c58de8`。
重排控制流后机器代码有变化，不能继续沿用第一阶段“BDA逐字节相同”的结论。
45536字节初始化数据、状态/记录尺寸、存档格式和资源库保持不变。

`tools/test_control_flow.py` 在主机 CPU 模型执行整理前、后的实际 MIPS 指令，比较返回、
状态、输入消耗及可观察调用。输入、绘制、弹窗与部分效果计算使用确定性边界模型。

| 用例组 | 通过数 |
| --- | ---: |
| 战略城市选择与查找图 | 3565 |
| 数值输入 | 520 |
| 动画延迟、存活计数及中断 | 608 |
| 武将/宝物列表与分页 | 10512 |
| 搜索事件、随机序列及发现条件 | 2304 |
| 战场输入、方向、触摸、计时与寄存器初值 | 1260 |
| 30种计谋的命中/状态/消耗/演出分派 | 2880 |
| 玩家攻守、电脑交战、空城、同势力入城和阵列排序 | 540 |
| 软浮点边界、舍入与确定性随机值 | 4974 |
| 合计 | 27163 |

另用独立测试 ELF 保留被生产链接器消除的运行库入口，完成60026组对照：
格式输出58516、整数/浮点/字符串字段1314、字符串转整数196。
测试 ELF 不进入发行 BDA；其中 `vformat` 本身没有被链接进生产镜像。

最终生产 BDA 重新通过593项既有 MIPS 回归和24项原生固件模拟器界面检查。
后者包含战略底栏6、制作群组2、受控战场界面12、居中天数弹窗4。
42个模块分别通过语法编译，资源回包10项、扩大资源库加载4项及89项资源代码用途检查通过。
这些结果支持已覆盖流程的行为一致，完整战役、全部AI分支和真机仍未系统验证。
原生模拟器继续使用原439720字节资源库；新版461116字节库的依据是主机回包和加载检查。

## 复验

在开始修改前保存该版 `build/sango.elf`、`src/`、`include/` 与 `source-map.json`。
本轮使用的基线是上面的 `ad129c1`，不能拿候选镜像自身当基线。
下面假定这些文件已放在 `build/readability-baseline/`，已有编译器可用 `SANGO_CC` 指定。

```powershell
python -m pip install -r requirements-validation.txt
python build.py
python tools/check_modules.py
python tools/test_control_flow.py --baseline build/readability-baseline/sango.elf

python tools/build_runtime_oracle.py --source-root build/readability-baseline --output build/runtime-before/sango.elf
python tools/build_runtime_oracle.py --output build/runtime-after/sango.elf
python tools/test_runtime_format.py --baseline build/runtime-before/sango.elf --candidate build/runtime-after/sango.elf

python tools/source_index.py --check
python tools/audit_resource_usage.py --check
```

主机对照不需要原版BDA、固件或NAND。原生固件检查使用本地私有诊断工具，未纳入公共CI；
诊断夹具和准确字节装载均不进入发行文件。机器可读摘要见
`validation/control-flow-refactor.json`，分组报告见同目录的 `control-flow-validation.json`、
`battle-register-validation.json` 和 `runtime-format-validation.json`。
