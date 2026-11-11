# 背景音乐

用户提供的三首完整 FLAC，经 `tools/music_assets.py` 转为适合9588的流式音乐资源。
原始母带留在用户本地，本目录只收录压缩后的运行文件及来源、转换参数和校验值。

| 场景 | 曲目 | 时长 | 文件 |
| --- | --- | --- | --- |
| 主菜单 | 谈笑风云·史诗主题 V2 | 4分22.36秒 | `runtime/menu.wav` |
| 策略 | 帷幄清风·策略谋划 | 1分50秒 | `runtime/strategy.wav` |
| 战斗 | 铁甲冲阵·器乐返修 V7 | 2分29.6秒 | `runtime/battle.wav` |

三首共5,834,932字节，保存为22050Hz、单声道、4位IMA ADPCM WAV，256字节一块。
游戏用固定小缓冲解码为SDK已验证的22050Hz、16位单声道PCM，不整首载入内存。
保留完整长度，仅首尾各20ms淡入淡出，自动循环；切换场景从对应曲目开头播放。
播放时显式初始化PCM衰减值24，结束恢复此前设置；外部音量控制仍由设备提供。
alpha.7增加4KiB压缩预读、限制单次PCM提交预算，普通版不输出诊断日志，详见 [音乐改进](../../docs/MUSIC_PLAYBACK.md)。

安装到 `应用/数据/游戏/sango-music/`。音乐缺失或格式损坏时静音运行，不影响菜单和游戏。
实际路径从已加载的 `sango.lib` 所在目录推导，不依赖中文曲名。
电脑自动处理的战斗继续策略曲，玩家观看/操作的战斗切换战斗曲；返回策略界面恢复策略曲。
退出应用关闭文件、播放和音乐定时器。

常规构建无需FFmpeg，验证并复制本目录已转换文件即可。
重新转换需要PATH中可用的FFmpeg/ffprobe（已验证5.1.2）和原始三首FLAC：

```powershell
python tools/music_assets.py --source-dir "PATH/TO/三国霸业"
python tools/music_assets.py
python tools/test_music.py
```

源目录下使用 `manifest.json` 的 `source_folder/source_file` 结构。
转换器记录母带SHA-256、精确样本数、压缩文件SHA-256、独立FFmpeg解码PCM校验和与SNR。
音乐不是MIT代码素材，未提供单独音乐再授权条款，见根目录来源声明。
