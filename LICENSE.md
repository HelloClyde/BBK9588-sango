# 许可证范围

本仓库不是整仓统一许可证。只有下列新增、独立编写的构建与适配代码采用 MIT：

- `build.py`、`tools/*.py` 和 `.github/workflows/release.yml`；
- `src/sango_entry.c`、`src/sango_statusbar.c`、`src/sango_credits.c`、`src/sango_battle_ui.c`；
- 与上述新模块对应的头文件，以及项目私有 `include/bda_sango_compat.h`、`include/sango_sdk_bindings.h`。

MIT 正文见 [LICENSES/MIT.txt](LICENSES/MIT.txt)。版权人为 2026 BBK9588-sango contributors。

原游戏恢复部分 `src/sango_game.c`、`src/sango_data.c`、`include/sango_recovered.h`，
原作布局/接口材料及原作派生图像，不包含在上述 MIT 授权中。本次没有提供原游戏的源码开源或
素材再分发许可，因此这里不替原作者授予额外权利。新增修复不能使原游戏整体自动获得 MIT 许可。

`sdk/` 子模块保留上游自己的 Apache-2.0 OR GPL-2.0-only 等声明，具体范围以上游为准。
SDK 的许可不覆盖原游戏、字库、原图、`sango.LIB` 或固件。
截图中含原游戏画面，GPT Image 图像也源于原图参考，均不作为 MIT 美术素材授权。

来源、作者、未提供的许可及不分发内容见 [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md)。
