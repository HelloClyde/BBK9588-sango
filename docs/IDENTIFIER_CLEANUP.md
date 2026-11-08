# 剩余短函数命名整理

本页为历史重构阶段记录；后续战斗底栏修复已改变BDA，最新结果见 [验证记录](VALIDATION.md)。

基线为 `301678844b8d283ad8d4fdcfb2ea2bb6dba891ba`，在第二阶段复杂流程整理之后继续处理短函数。
本轮覆盖32个模块的249个函数，重命名1516个变量或参数、54个标签。
446个恢复函数已全部移除 `uVar`、`iVar`、`param_N`、`local_地址`、栈/寄存器临时名及地址式标签。
原地址注释和 `source-map.json` 的历史映射继续用于追溯。

| 范围 | 命名依据 |
| --- | --- |
| 战斗移动、目标、状态、演出 | 单位/武将索引、移动窗口、相邻格、技力、伤害、恢复判定及动画帧 |
| 城市指令、名册与战后处理 | 城市/势力、执行者/目标、名册位置、指令字段、发展量及错误文字 |
| 界面、素材和存档 | 菜单边界、选中行、文本片段、位图平面、文件对和存档槽位 |
| SDK绑定与事件 | SDK窗口描述符字段、上下文、事件种类、按键、计时及文件返回值 |
| 软浮点与运行库 | 分类、符号、指数、尾数、商位、舍入及比较结果 |

例如状态更新的标签改为 `check_unit_status`、`check_status_recovery`、`apply_troop_attrition`、
`clear_unit_status` 和 `next_unit`；指令向导的公共错误出口改为 `show_command_error`。
本轮保留原跳转关系，131处 `goto` 的数量不变。

SDK窗口字段按固定版本SDK的 `bda_frame_desc_t` 命名；未确认的内部字段保留 `internal` / `aux`，
确实未使用的参数保留 `unused` 标记。没有根据变量类型推定业务含义。
部分旧存储会在不同阶段复用，`*_or_*` 名称列明这些角色；原复用关系和未初始化情形保持不变。

## 一致性证据

`tools/verify_identifier_rename.py` 从前后映射恢复名称替换关系，逐词核对全部446个函数，
要求声明、类型、常量、字符串、运算和控制流保持一致，只忽略注释与排版。
然后对生产BDA和资源库逐字节比较；任何差异都会使检查失败。

本轮结果：

- 446个函数核对通过，249个函数发生名称替换，剩余旧式临时名为0。
- ELF前后SHA-256相同：`ddd15b13e1abe4a7178e44ba65e2af447aea94b36840582fc9f5595d31085446`。
- BDA为214700字节，SHA-256仍为 `3f193d6e2f9a345b55f595ad7dbb93f4173dbc938088b42b744b5a6362c58de8`。
- `sango.lib` 为461116字节，SHA-256仍为 `01869a536d248156beef8d00c8185b5670731df82fbed39e9daba46fec8b2a11`。
- 42个模块分别编译通过，函数索引和89项资源代码依据核对通过。

游戏执行的机器代码、初始化数据及资源均未变化，沿用同一镜像已有的593项MIPS回归和24项原生固件
界面检查。本轮没有重新计入这些运行测试，也没有扩大完整战役、AI、时序或真机的验证范围。

## 复验

整理前保存 `src/`、`include/`、`source-map.json`，以及构建生成的 `sango.elf`、`三国霸业.bda`、
`sango.lib` 到同一个基线目录。可从上面的基线提交构建获得这些文件。
下面假定该目录为 `build/short-readability-baseline/`：

```powershell
python build.py
python tools/verify_identifier_rename.py --baseline build/short-readability-baseline
python tools/check_modules.py
python tools/source_index.py --check
python tools/audit_resource_usage.py --check
```

`source_index.py --check` 已加入旧式局部变量/标签检查，CI沿用该入口，防止后续改动重新引入。
完整机器可读结果见 `validation/identifier-rename-validation.json`；构建与源码摘要见
`validation/identifier-cleanup.json`。
