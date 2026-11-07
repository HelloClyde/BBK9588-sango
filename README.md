# BBK9588-sango（三国霸业 C 重建与兼容修复）

面向步步高 9588/C200 环境，将提供的《三国霸业》BDA 整理为可重新编译的 MIPS C 工程，
共 446 个恢复函数，并修复原 9588 移植中的状态栏、战斗动画、制作群组和战斗界面布局问题。
函数、变量仍包含恢复名称，本项目不是原开发者的工程。

当前版本为 **0.1.0-alpha.1**。本地发布准备已经完成，远程 Actions 和 Release 尚未执行。
原游戏恢复代码及改编素材没有已提供的开源许可证；新增独立代码与上游 SDK 的许可范围
分别记录于 [LICENSE.md](LICENSE.md) 和 [来源声明](THIRD_PARTY_NOTICES.md)，请勿将整仓视为 MIT 授权。

## 快速开始

发布前可按下方命令本地构建。正式发布后，从本仓库 Releases 选择同一版本的 BDA 或 `-update.zip`。
仅更换应用图标为 9288S 原图的彩色高清重绘，游戏内仍使用原灰度资源及已恢复的底栏。

适用于此前验证的 **9588/C200 固件环境**；不宣称适配所有 BBK 机型。
升级 ZIP 中的目录与设备内置存储根目录对应：

```text
应用/
└── 程序/
    └── 三国霸业.bda
```

设备还须已有 `应用/数据/游戏/sango.LIB`，439720 字节，SHA-256：
`42920210b5a130781ed1f1cce4bdaca3fc1bb95f14fac8d88d170a9ad77490a5`。
原 LIB 不随源码仓库或升级包分发，请沿用自己已有的原游戏安装资源。
本包不包含系统固件、原版 BDA、字库转储或个人存档。

升级前保留设备同名程序备份，把 `应用` 目录合并到内置存储根目录。
安全弹出设备、退出 USB 存储模式后，从“娱乐天地”打开《三国霸业》。不要把整个源码目录复制进设备。
程序沿用 `系统/数据/游戏/sango0.sav`、`sango1.sav` 等原存档路径，升级包不覆盖它们。

方向键选择／移动，确定执行，返回取消；触摸“信息／查找”打开相应信息页。
战斗状态行与按钮栏相邻，一位及两位天数弹窗均在屏幕中央。

### 开发者构建

在仓库根目录执行（Windows PowerShell，Python 3.11+）：

```powershell
git submodule update --init sdk
powershell -ExecutionPolicy Bypass -File sdk/scripts/setup_toolchain.ps1
python build.py
python tools/package_release.py --require-validated
python tools/verify_artifacts.py --require-validated
```

已有编译器时可指定路径：`python build.py --cc PATH/TO/mipsel-none-elf-gcc.exe`，
或设置 `SANGO_CC`。普通构建仅用 Python 标准库和固定 SDK，无需 Pillow、图像服务或原版 BDA。

输出 `build/三国霸业.bda`；打包输出在 `dist/`，包括独立 BDA、升级 ZIP、`BUILD_INFO.json`
及逐文件 `SHA256SUMS.txt`。普通构建不会发布任何远程内容。
`--require-validated` 要求输出哈希与保存的运行证据相符；修改代码后，须重新验证并更新参考记录。

## 截图

以下均为计划发布的确切 BDA 在本地 C200 固件模拟器中的真实截图，非真机截图或设计稿。
战斗图片来自受控战场界面夹具；未宣称完整战斗或战役已验证。

| 主菜单 | 战略地图 | 战斗界面 |
| --- | --- | --- |
| ![主菜单](docs/screenshots/main-menu.png) | ![战略地图](docs/screenshots/strategy.png) | ![战斗界面](docs/screenshots/battle.png) |

| 天数弹窗 | 制作群组 |
| --- | --- |
| ![第10天](docs/screenshots/day-10.png) | ![制作群组](docs/screenshots/credits.png) |

验证方法、精确哈希和未覆盖范围见 [验证记录](docs/VALIDATION.md)。

## 依赖

- **使用成品**：9588/C200 环境和自己已有的原 `sango.LIB`，不需要 SDK 或 Python。
- **SDK**：[HelloClyde/BBK9588-bda-sdk](https://github.com/HelloClyde/BBK9588-bda-sdk)，
  子模块固定 `ef3bf3b7328a3a8fa9ba48593c63285300725fb7`，没有自动升级。
- **工具链**：MIPS O32 小端、soft-float，已验证 GCC 15.2.0；SDK 安装脚本校验工具链 ZIP 的 SHA-256。
- **构建**：Git 和 Python 3.11+；本地验证使用 Python 3.11.5，CI 配置为 Python 3.12/Windows。
- **重新生成素材**：仅此步骤需要 `python -m pip install -r requirements-assets.txt`（Pillow 12.3.0）。
  母图与提示词已保存。`tools/pack_*.py` 只重新编码已有母图，不访问图像生成服务。
- **模拟器复验**：用户自行提供兼容 QEMU、C200 固件和 NAND；它们不会上传仓库或 CI。

项目私有的 SDK 兼容扩展放在 `include/bda_sango_compat.h`，不会修改 `sdk/` 子模块。
公共 SDK 接口可用后，通过 `include/sango_sdk_bindings.h` 切换，游戏调用处保持命名接口。

## 感谢

- 原游戏制作群组：策划 **BBK gamegroup**；程序 **通宵虫、南方小凯**；美工 **Sunday**。
- **HelloClyde / BBK9588-bda-sdk**：SDK、BDA 编码与校验工具。
- 提供原文件、9588 真机反馈、9288S 对照及修复需求的使用者。
- 应用图标、恢复底栏和制作群组母图通过 GPT Image 生成；来源和提示词在 `assets/` 中保存。

致谢不改变原作、SDK 或素材的许可范围。发布步骤见 [发布说明](docs/RELEASING.md)。
