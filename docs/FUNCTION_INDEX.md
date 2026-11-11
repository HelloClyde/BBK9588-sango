# 函数索引

由 `python tools/source_index.py` 生成；手工阅读入口见 [源码导航](SOURCE_GUIDE.md)。
原地址用于对照恢复记录，不代表重新链接后的函数地址。未确认的兼容空入口保留 `stub` 名称。

## src/app/boot.c

入口及旧版状态区初始化。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c00020` | [`bda_entry`](../src/app/boot.c#L6) |
| `0x81c00050` | [`bda_runtime_init`](../src/app/boot.c#L14) |

## src/battle/army.c

战场队伍索引与兵力合计。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c001a0` | [`sango_battle_choose_auto_result`](../src/battle/army.c#L6) |
| `0x81c002b4` | [`sango_battle_sum_side_troops`](../src/battle/army.c#L47) |
| `0x81c0036c` | [`sango_battle_character_id`](../src/battle/army.c#L72) |

## src/battle/movement.c

地形成本、移动范围与可达位置。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c003b8` | [`sango_battle_build_move_range`](../src/battle/movement.c#L6) |
| `0x81c00558` | [`sango_battle_copy_move_window`](../src/battle/movement.c#L91) |
| `0x81c00784` | [`sango_battle_load_movement_costs`](../src/battle/movement.c#L179) |
| `0x81c00870` | [`sango_battle_expand_reachable_tiles`](../src/battle/movement.c#L212) |
| `0x81c00954` | [`sango_battle_relax_move_costs`](../src/battle/movement.c#L252) |
| `0x81c00b18` | [`sango_battle_mark_blocked_positions`](../src/battle/movement.c#L312) |

## src/battle/combat_math.c

部队属性与伤害计算。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c00bfc` | [`sango_battle_initialize_unit_stats`](../src/battle/combat_math.c#L6) |
| `0x81c00e90` | [`sango_battle_refresh_unit_stats`](../src/battle/combat_math.c#L96) |
| `0x81c0108c` | [`sango_battle_remove_unit_status`](../src/battle/combat_math.c#L163) |
| `0x81c0118c` | [`sango_battle_roll_attack_damage`](../src/battle/combat_math.c#L207) |
| `0x81c01278` | [`sango_battle_prepare_combatant`](../src/battle/combat_math.c#L234) |
| `0x81c0142c` | [`sango_battle_consume_daily_food`](../src/battle/combat_math.c#L295) |
| `0x81c014bc` | [`sango_battle_subtract_clamped`](../src/battle/combat_math.c#L326) |
| `0x81c014ec` | [`sango_battle_add_clamped`](../src/battle/combat_math.c#L345) |
| `0x81c01524` | [`sango_battle_compute_skill_effect`](../src/battle/combat_math.c#L365) |

## src/battle/ai.c

电脑部队行动与目标选择。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c017a0` | [`sango_battle_ai_plan_unit`](../src/battle/ai.c#L6) |
| `0x81c018b0` | [`sango_battle_ai_choose_skill`](../src/battle/ai.c#L45) |
| `0x81c01af0` | [`sango_battle_ai_prepare_attack`](../src/battle/ai.c#L137) |
| `0x81c01b68` | [`sango_battle_ai_choose_destination`](../src/battle/ai.c#L160) |
| `0x81c01e74` | [`sango_battle_choose_skill`](../src/battle/ai.c#L300) |
| `0x81c01fbc` | [`sango_battle_skill_target_allowed`](../src/battle/ai.c#L354) |
| `0x81c0205c` | [`sango_battle_collect_unit_skills`](../src/battle/ai.c#L374) |
| `0x81c021d4` | [`sango_battle_load_skill_names`](../src/battle/ai.c#L417) |
| `0x81c02244` | [`sango_battle_skill_terrain_allowed`](../src/battle/ai.c#L441) |
| `0x81c02314` | [`sango_battle_unit_terrain`](../src/battle/ai.c#L466) |
| `0x81c02354` | [`sango_battle_select_combat_target`](../src/battle/ai.c#L478) |
| `0x81c02444` | [`sango_battle_target_in_skill_range`](../src/battle/ai.c#L522) |
| `0x81c024a0` | [`sango_battle_preview_skill_range`](../src/battle/ai.c#L543) |
| `0x81c02524` | [`sango_battle_load_range_template`](../src/battle/ai.c#L566) |
| `0x81c02664` | [`sango_battle_select_ai_unit`](../src/battle/ai.c#L610) |
| `0x81c0272c` | [`sango_battle_distance_components`](../src/battle/ai.c#L651) |
| `0x81c027a0` | [`sango_battle_manhattan_distance`](../src/battle/ai.c#L665) |

## src/battle/overview.c

可移动区域及战场形势信息。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c027f0` | [`sango_battle_draw_move_range`](../src/battle/overview.c#L6) |
| `0x81c02954` | [`sango_battle_show_overview`](../src/battle/overview.c#L55) |
| `0x81c02c4c` | [`sango_battle_draw_overview_rows`](../src/battle/overview.c#L176) |
| `0x81c02ec0` | [`sango_battle_count_active_units`](../src/battle/overview.c#L256) |
| `0x81c02f08` | [`sango_battle_load_overview_text`](../src/battle/overview.c#L273) |
| `0x81c02f30` | [`sango_battle_is_player_unit`](../src/battle/overview.c#L280) |

## src/battle/player_turn.c

部队回合、操作命令与目标输入。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c02f4c` | [`sango_battle_plan_ai_action`](../src/battle/player_turn.c#L6) |
| `0x81c03020` | [`sango_battle_run_player_turn`](../src/battle/player_turn.c#L40) |
| `0x81c03154` | [`sango_battle_show_unit_commands`](../src/battle/player_turn.c#L95) |
| `0x81c032d4` | [`sango_battle_select_target`](../src/battle/player_turn.c#L156) |
| `0x81c0343c` | [`sango_battle_draw_target_markers`](../src/battle/player_turn.c#L227) |
| `0x81c03590` | [`sango_battle_filter_unit_commands`](../src/battle/player_turn.c#L282) |
| `0x81c03654` | [`sango_battle_finish_unit_action`](../src/battle/player_turn.c#L320) |
| `0x81c03708` | [`sango_battle_select_move_destination`](../src/battle/player_turn.c#L348) |
| `0x81c03874` | [`sango_battle_select_active_unit`](../src/battle/player_turn.c#L400) |
| `0x81c038f4` | [`sango_battle_poll_map_action`](../src/battle/player_turn.c#L426) |
| `0x81c03c20` | [`sango_battle_draw_cursor`](../src/battle/player_turn.c#L558) |

## src/battle/field.c

战场初始化、日更新与地图绘制。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c03c98` | [`sango_battle_initialize_field`](../src/battle/field.c#L6) |
| `0x81c03ea8` | [`sango_battle_spawn_origin`](../src/battle/field.c#L93) |
| `0x81c03f6c` | [`sango_battle_draw_hud`](../src/battle/field.c#L132) |
| `0x81c03ff8` | [`sango_battle_target_side_allowed`](../src/battle/field.c#L139) |
| `0x81c04064` | [`sango_battle_advance_day`](../src/battle/field.c#L161) |
| `0x81c041f8` | [`sango_battle_scroll_viewport`](../src/battle/field.c#L215) |
| `0x81c042c4` | [`sango_battle_tick_unit_statuses`](../src/battle/field.c#L252) |
| `0x81c04468` | [`sango_battle_redraw_field`](../src/battle/field.c#L334) |
| `0x81c044f8` | [`sango_battle_show_unit_delta`](../src/battle/field.c#L361) |
| `0x81c04590` | [`sango_battle_blink_unit`](../src/battle/field.c#L385) |
| `0x81c04630` | [`sango_battle_draw_units`](../src/battle/field.c#L408) |
| `0x81c047bc` | [`sango_battle_draw_tile`](../src/battle/field.c#L459) |
| `0x81c048bc` | [`sango_battle_show_action_message`](../src/battle/field.c#L494) |
| `0x81c04920` | [`sango_battle_check_level_and_retreat`](../src/battle/field.c#L510) |
| `0x81c04ae8` | [`sango_battle_play_unit_effect`](../src/battle/field.c#L570) |
| `0x81c04b9c` | [`sango_battle_draw_terrain`](../src/battle/field.c#L594) |
| `0x81c04c60` | [`sango_battle_copy_viewport_tiles`](../src/battle/field.c#L618) |
| `0x81c04d58` | [`sango_battle_draw_cursor_description`](../src/battle/field.c#L654) |
| `0x81c04e34` | [`sango_battle_check_finish`](../src/battle/field.c#L686) |
| `0x81c04efc` | [`sango_battle_unit_character`](../src/battle/field.c#L732) |
| `0x81c04f18` | [`sango_battle_load_text`](../src/battle/field.c#L738) |
| `0x81c04f40` | [`sango_battle_resource_item`](../src/battle/field.c#L745) |
| `0x81c04f68` | [`sango_battle_present`](../src/battle/field.c#L754) |
| `0x81c04f8c` | [`sango_battle_draw_text`](../src/battle/field.c#L761) |
| `0x81c04fb4` | [`sango_battle_draw_bitmap`](../src/battle/field.c#L768) |

## src/battle/controller.c

战斗主循环与界面恢复。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c04fe0` | [`sango_battle_run`](../src/battle/controller.c#L7) |
| `0x81c051e8` | [`sango_battle_begin`](../src/battle/controller.c#L97) |
| `0x81c052cc` | [`sango_battle_run_ai_turn`](../src/battle/controller.c#L134) |
| `0x81c053c4` | [`sango_battle_refresh_target_preview`](../src/battle/controller.c#L182) |
| `0x81c05400` | [`sango_battle_refresh_move_preview`](../src/battle/controller.c#L196) |
| `0x81c0543c` | [`sango_battle_reset_session`](../src/battle/controller.c#L210) |
| `0x81c054a0` | [`sango_battle_refresh_display`](../src/battle/controller.c#L228) |
| `0x81c054e4` | [`sango_battle_focus_viewport`](../src/battle/controller.c#L239) |
| `0x81c055b0` | [`sango_battle_show_cursor_info`](../src/battle/controller.c#L269) |

## src/battle/actions.c

普通攻击、计谋执行和演出反馈。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c058b8` | [`sango_battle_execute_skill`](../src/battle/actions.c#L7) |
| `0x81c05cdc` | [`sango_battle_execute_surround_attack`](../src/battle/actions.c#L173) |
| `0x81c05e0c` | [`sango_battle_execute_normal_attack`](../src/battle/actions.c#L227) |
| `0x81c05f7c` | [`sango_battle_draw_damage_digits`](../src/battle/actions.c#L284) |
| `0x81c060c8` | [`sango_battle_append_stat_value`](../src/battle/actions.c#L335) |
| `0x81c06168` | [`sango_battle_damage_feedback`](../src/battle/actions.c#L368) |
| `0x81c0620c` | [`sango_battle_terrain_at`](../src/battle/actions.c#L388) |
| `0x81c062d0` | [`sango_battle_skill_parameters`](../src/battle/actions.c#L426) |
| `0x81c06318` | [`sango_battle_find_unit_at`](../src/battle/actions.c#L435) |
| `0x81c06384` | [`sango_battle_change_weather`](../src/battle/actions.c#L458) |
| `0x81c06440` | [`sango_battle_show_options`](../src/battle/actions.c#L474) |
| `0x81c065c4` | [`sango_battle_draw_unit_damage`](../src/battle/actions.c#L549) |
| `0x81c06650` | [`sango_battle_resolve_character`](../src/battle/actions.c#L572) |
| `0x81c0666c` | [`sango_battle_read_text`](../src/battle/actions.c#L578) |
| `0x81c06694` | [`sango_battle_execute_action`](../src/battle/actions.c#L585) |
| `0x81c06838` | [`sango_battle_unit_sprite_frame`](../src/battle/actions.c#L647) |
| `0x81c068f0` | [`sango_battle_regenerate_unit_energy`](../src/battle/actions.c#L680) |
| `0x81c069d4` | [`sango_battle_find_actionable_unit_at_cursor`](../src/battle/actions.c#L706) |

## src/render/animation.c

五字节指令时间轴播放器。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c06a70` | [`sango_animation_play_range`](../src/render/animation.c#L7) |

## src/ui/menu_and_text.c

选项菜单、位图控件、文本布局与数值提示。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c07068` | [`sango_ui_choose_option`](../src/ui/menu_and_text.c#L6) |
| `0x81c077bc` | [`sango_bitmap_draw_resource`](../src/ui/menu_and_text.c#L243) |
| `0x81c0791c` | [`sango_text_draw_wrapped_box`](../src/ui/menu_and_text.c#L303) |
| `0x81c079fc` | [`sango_text_wrap_lines`](../src/ui/menu_and_text.c#L354) |
| `0x81c07b20` | [`sango_text_find_line_end`](../src/ui/menu_and_text.c#L397) |
| `0x81c07b58` | [`sango_text_draw_centered`](../src/ui/menu_and_text.c#L416) |
| `0x81c07bc0` | [`sango_battle_show_short_message`](../src/ui/menu_and_text.c#L426) |
| `0x81c07cac` | [`sango_math_sqrt_step_search`](../src/ui/menu_and_text.c#L448) |
| `0x81c07cf0` | [`sango_text_draw_padded_number`](../src/ui/menu_and_text.c#L472) |
| `0x81c07e10` | [`sango_character_troop_capacity`](../src/ui/menu_and_text.c#L517) |

## src/platform/window_graphics.c

SDK窗口消息及基础绘图适配。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c07e70` | [`sango_window_proc`](../src/platform/window_graphics.c#L6) |
| `0x81c07fd4` | [`sango_display_copy_and_refresh`](../src/platform/window_graphics.c#L57) |
| `0x81c08100` | [`sango_display_fill_rectangle`](../src/platform/window_graphics.c#L90) |
| `0x81c082fc` | [`sango_display_blit_palette_bitmap`](../src/platform/window_graphics.c#L148) |
| `0x81c0863c` | [`sango_display_capture_bitmap`](../src/platform/window_graphics.c#L276) |
| `0x81c0886c` | [`sango_display_put_gray_pixel`](../src/platform/window_graphics.c#L375) |
| `0x81c089c4` | [`sango_display_draw_line`](../src/platform/window_graphics.c#L436) |
| `0x81c08e7c` | [`sango_display_draw_rectangle`](../src/platform/window_graphics.c#L650) |
| `0x81c090c4` | [`sango_display_draw_circle`](../src/platform/window_graphics.c#L740) |
| `0x81c093c0` | [`sango_display_draw_polyline`](../src/platform/window_graphics.c#L840) |
| `0x81c095b4` | [`sango_display_set_brush`](../src/platform/window_graphics.c#L904) |
| `0x81c09680` | [`sango_display_set_text_color`](../src/platform/window_graphics.c#L943) |
| `0x81c0974c` | [`sango_display_select_font`](../src/platform/window_graphics.c#L982) |

## src/platform/input_dialog.c

按键数据与文本输入对话框。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c097f4` | [`sango_bitmap_open_embedded_entry`](../src/platform/input_dialog.c#L6) |
| `0x81c098b4` | [`sango_input_key_is_down`](../src/platform/input_dialog.c#L50) |
| `0x81c09990` | [`sango_raster_invert_packed_rectangle`](../src/platform/input_dialog.c#L78) |
| `0x81c09b6c` | [`sango_text_input_proc`](../src/platform/input_dialog.c#L157) |
| `0x81c09d90` | [`sango_text_input_dialog`](../src/platform/input_dialog.c#L203) |
| `0x81c09fb0` | [`sango_display_render_bitmap_region`](../src/platform/input_dialog.c#L289) |
| `0x81c0a2c0` | [`sango_platform_window_auxiliary`](../src/platform/input_dialog.c#L395) |

## src/platform/sdk_bindings.c

应用窗口、计时、内存、文件和消息框适配。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c0a330` | [`sango_create_app_frame`](../src/platform/sdk_bindings.c#L6) |
| `0x81c0a44c` | [`sango_platform_allocate_zeroed_buffer`](../src/platform/sdk_bindings.c#L72) |
| `0x81c0a4a4` | [`sango_run_event_loop_and_close`](../src/platform/sdk_bindings.c#L86) |
| `0x81c0a578` | [`sango_platform_init_window_descriptor`](../src/platform/sdk_bindings.c#L112) |
| `0x81c0a5fc` | [`sango_input_poll_native_event`](../src/platform/sdk_bindings.c#L134) |
| `0x81c0a6a0` | [`bbk_post_message`](../src/platform/sdk_bindings.c#L156) |
| `0x81c0a704` | [`bbk_alloc`](../src/platform/sdk_bindings.c#L177) |
| `0x81c0a72c` | [`bbk_free_if_nonnull`](../src/platform/sdk_bindings.c#L186) |
| `0x81c0a774` | [`bbk_strcat`](../src/platform/sdk_bindings.c#L196) |
| `0x81c0a790` | [`bbk_strlen`](../src/platform/sdk_bindings.c#L205) |
| `0x81c0a7ac` | [`bbk_memcpy`](../src/platform/sdk_bindings.c#L214) |
| `0x81c0a7c8` | [`sango_memory_fill`](../src/platform/sdk_bindings.c#L223) |
| `0x81c0a7e4` | [`sango_format_integer`](../src/platform/sdk_bindings.c#L230) |
| `0x81c0a86c` | [`bbk_zero_time_stub`](../src/platform/sdk_bindings.c#L258) |
| `0x81c0a890` | [`bbk_srand`](../src/platform/sdk_bindings.c#L272) |
| `0x81c0a8ac` | [`bbk_rand`](../src/platform/sdk_bindings.c#L279) |
| `0x81c0a8c8` | [`sango_timer_start`](../src/platform/sdk_bindings.c#L288) |
| `0x81c0a904` | [`sango_timer_stop`](../src/platform/sdk_bindings.c#L295) |
| `0x81c0a938` | [`bbk_compatible_context_create`](../src/platform/sdk_bindings.c#L302) |
| `0x81c0a964` | [`bbk_compatible_context_free`](../src/platform/sdk_bindings.c#L311) |
| `0x81c0a990` | [`sango_display_present_context`](../src/platform/sdk_bindings.c#L318) |
| `0x81c0aadc` | [`sango_display_noop`](../src/platform/sdk_bindings.c#L348) |
| `0x81c0aae4` | [`sango_display_invert_rectangle`](../src/platform/sdk_bindings.c#L354) |
| `0x81c0abcc` | [`sango_platform_noop`](../src/platform/sdk_bindings.c#L383) |
| `0x81c0ac00` | [`sango_bitmap_query_dimensions`](../src/platform/sdk_bindings.c#L392) |
| `0x81c0ac48` | [`sango_display_fill_gray_rectangle`](../src/platform/sdk_bindings.c#L413) |
| `0x81c0ad1c` | [`sango_text_get_font_metrics`](../src/platform/sdk_bindings.c#L429) |
| `0x81c0addc` | [`sango_text_draw_native`](../src/platform/sdk_bindings.c#L444) |
| `0x81c0aeb0` | [`bbk_clearerr`](../src/platform/sdk_bindings.c#L460) |
| `0x81c0aed8` | [`bbk_ferror`](../src/platform/sdk_bindings.c#L467) |
| `0x81c0af00` | [`bbk_fclose`](../src/platform/sdk_bindings.c#L476) |
| `0x81c0af28` | [`bbk_feof`](../src/platform/sdk_bindings.c#L485) |
| `0x81c0af50` | [`sango_platform_stub_0af50`](../src/platform/sdk_bindings.c#L494) |
| `0x81c0af58` | [`sango_platform_stub_0af58`](../src/platform/sdk_bindings.c#L500) |
| `0x81c0af60` | [`bbk_fopen`](../src/platform/sdk_bindings.c#L506) |
| `0x81c0af88` | [`sango_platform_stub_0af88`](../src/platform/sdk_bindings.c#L515) |
| `0x81c0af90` | [`sango_platform_stub_0af90`](../src/platform/sdk_bindings.c#L521) |
| `0x81c0af98` | [`bbk_fread`](../src/platform/sdk_bindings.c#L527) |
| `0x81c0afdc` | [`bbk_fseek`](../src/platform/sdk_bindings.c#L537) |
| `0x81c0b004` | [`bbk_ftell`](../src/platform/sdk_bindings.c#L546) |
| `0x81c0b02c` | [`bbk_fwrite`](../src/platform/sdk_bindings.c#L555) |
| `0x81c0b070` | [`sango_platform_stub_0b070`](../src/platform/sdk_bindings.c#L565) |
| `0x81c0b078` | [`sango_platform_stub_0b078`](../src/platform/sdk_bindings.c#L571) |
| `0x81c0b080` | [`sango_platform_stub_0b080`](../src/platform/sdk_bindings.c#L577) |
| `0x81c0b088` | [`sango_platform_stub_0b088`](../src/platform/sdk_bindings.c#L583) |
| `0x81c0b090` | [`sango_platform_stub_0b090`](../src/platform/sdk_bindings.c#L589) |
| `0x81c0b098` | [`bbk_rename`](../src/platform/sdk_bindings.c#L595) |
| `0x81c0b0c0` | [`sango_platform_stub_0b0c0`](../src/platform/sdk_bindings.c#L604) |
| `0x81c0b0c8` | [`bbk_load_file_with_progress`](../src/platform/sdk_bindings.c#L610) |
| `0x81c0b2c4` | [`sango_platform_stub_0b2c4`](../src/platform/sdk_bindings.c#L657) |
| `0x81c0b2cc` | [`sango_platform_stub_0b2cc`](../src/platform/sdk_bindings.c#L663) |
| `0x81c0b2d4` | [`sango_platform_stub_0b2d4`](../src/platform/sdk_bindings.c#L669) |
| `0x81c0b404` | [`sango_input_dispatch_pending_events`](../src/platform/sdk_bindings.c#L675) |
| `0x81c0b500` | [`graphics_init_stub`](../src/platform/sdk_bindings.c#L714) |
| `0x81c0b508` | [`sango_platform_stub_0b508`](../src/platform/sdk_bindings.c#L720) |
| `0x81c0b510` | [`bbk_message_box`](../src/platform/sdk_bindings.c#L726) |

## src/strategy/domestic.c

内政、俘虏、赏赐与交易等城市命令。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c0b6f0` | [`sango_strategy_resolve_search`](../src/strategy/domestic.c#L6) |
| `0x81c0bc70` | [`sango_strategy_resolve_sow_discord`](../src/strategy/domestic.c#L177) |
| `0x81c0bf24` | [`sango_strategy_resolve_recruit`](../src/strategy/domestic.c#L271) |
| `0x81c0c168` | [`sango_strategy_resolve_defection`](../src/strategy/domestic.c#L345) |
| `0x81c0c490` | [`sango_strategy_resolve_surrender`](../src/strategy/domestic.c#L453) |
| `0x81c0c754` | [`sango_strategy_resolve_diplomatic_mission`](../src/strategy/domestic.c#L549) |
| `0x81c0cb64` | [`sango_strategy_resolve_plunder`](../src/strategy/domestic.c#L712) |
| `0x81c0cd08` | [`sango_strategy_execute_queued_order`](../src/strategy/domestic.c#L766) |
| `0x81c0d03c` | [`sango_strategy_find_ready_order`](../src/strategy/domestic.c#L885) |
| `0x81c0d0e4` | [`sango_strategy_return_order_character`](../src/strategy/domestic.c#L940) |
| `0x81c0d304` | [`sango_strategy_success_stub`](../src/strategy/domestic.c#L948) |
| `0x81c0d354` | [`sango_strategy_advance_orders`](../src/strategy/domestic.c#L954) |
| `0x81c0d3e0` | [`sango_city_choose_command`](../src/strategy/domestic.c#L976) |
| `0x81c0d498` | [`sango_city_choose_command_group`](../src/strategy/domestic.c#L1026) |
| `0x81c0d4f8` | [`sango_city_choose_domestic_command`](../src/strategy/domestic.c#L1046) |
| `0x81c0d558` | [`sango_city_choose_diplomacy_command`](../src/strategy/domestic.c#L1066) |
| `0x81c0d5b8` | [`sango_city_choose_military_command`](../src/strategy/domestic.c#L1086) |

## src/strategy/orders.c

战略命令选择、目标及执行队列。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c0d618` | [`sango_city_execute_command`](../src/strategy/orders.c#L7) |
| `0x81c0d7e4` | [`sango_city_order_agriculture`](../src/strategy/orders.c#L124) |
| `0x81c0da0c` | [`sango_city_order_commerce`](../src/strategy/orders.c#L224) |
| `0x81c0dc30` | [`sango_city_show_development_result`](../src/strategy/orders.c#L324) |
| `0x81c0ddf0` | [`sango_city_order_search`](../src/strategy/orders.c#L378) |
| `0x81c0df94` | [`sango_city_order_disaster_prevention`](../src/strategy/orders.c#L454) |
| `0x81c0e184` | [`sango_city_order_patrol`](../src/strategy/orders.c#L547) |
| `0x81c0e38c` | [`sango_city_order_recruit_captive`](../src/strategy/orders.c#L643) |
| `0x81c0e53c` | [`sango_city_order_execute_captive`](../src/strategy/orders.c#L726) |
| `0x81c0e6c4` | [`sango_city_order_exile_character`](../src/strategy/orders.c#L775) |
| `0x81c0e87c` | [`sango_city_order_reward`](../src/strategy/orders.c#L840) |
| `0x81c0eb10` | [`sango_city_order_trade`](../src/strategy/orders.c#L943) |
| `0x81c0ed78` | [`sango_city_order_banquet`](../src/strategy/orders.c#L1049) |

## src/strategy/military.c

军事行动、出征编队与进入战斗。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c0ef00` | [`sango_city_order_transport`](../src/strategy/military.c#L6) |
| `0x81c0f244` | [`sango_city_order_transfer`](../src/strategy/military.c#L187) |
| `0x81c0f49c` | [`sango_city_order_sow_discord`](../src/strategy/military.c#L297) |
| `0x81c0f61c` | [`sango_city_order_recruit_enemy`](../src/strategy/military.c#L373) |
| `0x81c0f7a0` | [`sango_city_order_defection`](../src/strategy/military.c#L447) |
| `0x81c0f934` | [`sango_city_order_demand_surrender`](../src/strategy/military.c#L526) |
| `0x81c0fab8` | [`sango_city_order_scout`](../src/strategy/military.c#L599) |
| `0x81c0fca4` | [`sango_city_order_recruit_troops`](../src/strategy/military.c#L695) |
| `0x81c0fe88` | [`sango_city_assign_troops`](../src/strategy/military.c#L781) |
| `0x81c10020` | [`sango_city_order_counterintelligence`](../src/strategy/military.c#L864) |
| `0x81c10050` | [`sango_city_order_attack`](../src/strategy/military.c#L871) |
| `0x81c10394` | [`sango_strategy_resolve_attack`](../src/strategy/military.c#L995) |
| `0x81c10a4c` | [`sango_strategy_finish_battle`](../src/strategy/military.c#L1291) |

## src/strategy/aftermath.c

战后处理、君主继承和战斗事件提示。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c10d6c` | [`sango_strategy_handle_defeated_units`](../src/strategy/aftermath.c#L6) |
| `0x81c10f78` | [`sango_character_return_to_city`](../src/strategy/aftermath.c#L91) |
| `0x81c10fdc` | [`sango_character_escape_to_friendly_city`](../src/strategy/aftermath.c#L108) |
| `0x81c1107c` | [`sango_city_choose_postbattle_governor`](../src/strategy/aftermath.c#L137) |
| `0x81c11188` | [`sango_strategy_resolve_ruler_succession`](../src/strategy/aftermath.c#L192) |
| `0x81c11404` | [`sango_strategy_show_new_ruler`](../src/strategy/aftermath.c#L308) |
| `0x81c11494` | [`sango_strategy_show_ruler_changed`](../src/strategy/aftermath.c#L325) |
| `0x81c114fc` | [`sango_strategy_show_faction_destroyed`](../src/strategy/aftermath.c#L340) |
| `0x81c11564` | [`sango_strategy_queue_army`](../src/strategy/aftermath.c#L355) |
| `0x81c11638` | [`sango_strategy_show_ruler_defection`](../src/strategy/aftermath.c#L388) |
| `0x81c116a0` | [`sango_strategy_show_recruit_success`](../src/strategy/aftermath.c#L403) |
| `0x81c116f0` | [`sango_strategy_enqueue_order`](../src/strategy/aftermath.c#L414) |
| `0x81c11758` | [`sango_strategy_remove_order`](../src/strategy/aftermath.c#L437) |
| `0x81c117c0` | [`sango_strategy_queue_noop`](../src/strategy/aftermath.c#L460) |
| `0x81c117d0` | [`sango_city_order_confiscate`](../src/strategy/aftermath.c#L467) |
| `0x81c11a2c` | [`sango_city_order_plunder`](../src/strategy/aftermath.c#L564) |
| `0x81c11b50` | [`sango_character_can_pay_action`](../src/strategy/aftermath.c#L617) |
| `0x81c11bbc` | [`sango_character_pay_action`](../src/strategy/aftermath.c#L627) |
| `0x81c11c28` | [`sango_city_find_weakest_target`](../src/strategy/aftermath.c#L640) |
| `0x81c11d98` | [`sango_strategy_show_army_attack`](../src/strategy/aftermath.c#L711) |
| `0x81c11f18` | [`sango_strategy_show_armies_engage`](../src/strategy/aftermath.c#L743) |
| `0x81c12058` | [`sango_strategy_show_battle_victory`](../src/strategy/aftermath.c#L768) |
| `0x81c12188` | [`sango_strategy_show_battle_defeat`](../src/strategy/aftermath.c#L796) |

## src/strategy/rosters.c

行动消耗、武将宝物列表与城市关系。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c12308` | [`sango_city_can_pay_command`](../src/strategy/rosters.c#L6) |
| `0x81c12374` | [`sango_city_pay_command`](../src/strategy/rosters.c#L16) |
| `0x81c123f0` | [`sango_city_remove_character`](../src/strategy/rosters.c#L28) |
| `0x81c12504` | [`sango_city_remove_item`](../src/strategy/rosters.c#L72) |
| `0x81c1261c` | [`sango_city_route_distance`](../src/strategy/rosters.c#L116) |
| `0x81c127ec` | [`sango_city_find_neighbor`](../src/strategy/rosters.c#L216) |
| `0x81c128b4` | [`sango_city_find_neighbor_position`](../src/strategy/rosters.c#L252) |
| `0x81c1297c` | [`sango_city_list_enemy_neighbors`](../src/strategy/rosters.c#L291) |
| `0x81c12a68` | [`sango_strategy_list_rulers`](../src/strategy/rosters.c#L333) |

## src/strategy/map.c

战略地图、城市选择和归属查询。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c12b18` | [`sango_strategy_select_city`](../src/strategy/map.c#L7) |
| `0x81c12e18` | [`sango_strategy_draw_map`](../src/strategy/map.c#L163) |
| `0x81c13494` | [`sango_strategy_present`](../src/strategy/map.c#L351) |
| `0x81c134b8` | [`sango_city_add_character`](../src/strategy/map.c#L358) |
| `0x81c135a8` | [`sango_city_add_item`](../src/strategy/map.c#L401) |
| `0x81c13698` | [`sango_city_roster_noop`](../src/strategy/map.c#L443) |
| `0x81c136a0` | [`sango_city_adjacent_distance`](../src/strategy/map.c#L449) |
| `0x81c13794` | [`sango_faction_list_cities`](../src/strategy/map.c#L501) |
| `0x81c137f0` | [`sango_character_find_city`](../src/strategy/map.c#L523) |
| `0x81c13870` | [`sango_city_list_idle_characters`](../src/strategy/map.c#L554) |
| `0x81c13918` | [`sango_city_list_available_characters`](../src/strategy/map.c#L584) |
| `0x81c139a8` | [`sango_city_list_captives`](../src/strategy/map.c#L614) |
| `0x81c13a40` | [`sango_city_list_enemy_rulers`](../src/strategy/map.c#L644) |
| `0x81c13ab8` | [`sango_faction_list_characters`](../src/strategy/map.c#L678) |

## src/ui/numeric.c

粮食、金钱、兵力输入面板。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c13b9c` | [`sango_ui_input_food_amount`](../src/ui/numeric.c#L6) |
| `0x81c13c3c` | [`sango_ui_input_money_amount`](../src/ui/numeric.c#L23) |
| `0x81c13cdc` | [`sango_ui_input_troop_amount`](../src/ui/numeric.c#L40) |

## src/app/memory.c

资源库及会话缓冲区生命周期。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c13d80` | [`sango_load_package_and_buffers`](../src/app/memory.c#L7) |
| `0x81c13f64` | [`sango_release_package_and_buffers`](../src/app/memory.c#L75) |

## src/platform/event_loop.c

事件规范化、等待及按键探测。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c1408c` | [`sango_input_next_event`](../src/platform/event_loop.c#L6) |
| `0x81c14164` | [`sango_input_wait`](../src/platform/event_loop.c#L42) |
| `0x81c14268` | [`sango_input_peek_key`](../src/platform/event_loop.c#L92) |
| `0x81c14298` | [`sango_runtime_noop_a`](../src/platform/event_loop.c#L114) |
| `0x81c142a0` | [`sango_runtime_noop_b`](../src/platform/event_loop.c#L120) |
| `0x81c142a8` | [`sango_runtime_read_tick_counter`](../src/platform/event_loop.c#L126) |

## src/render/raster.c

四灰度位图、遮罩、文字及上下文呈现。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c14350` | [`sango_raster_draw_screen`](../src/render/raster.c#L6) |
| `0x81c14504` | [`sango_raster_draw_opaque`](../src/render/raster.c#L84) |
| `0x81c14690` | [`sango_raster_draw_masked`](../src/render/raster.c#L155) |
| `0x81c14838` | [`sango_raster_draw_masked_screen`](../src/render/raster.c#L244) |
| `0x81c149dc` | [`sango_text_draw_legacy`](../src/render/raster.c#L330) |
| `0x81c14cac` | [`sango_font_load_glyph`](../src/render/raster.c#L443) |
| `0x81c14d98` | [`sango_font_glyph_offset`](../src/render/raster.c#L486) |
| `0x81c14dd8` | [`sango_ui_show_message`](../src/render/raster.c#L493) |
| `0x81c14f98` | [`sango_render_present`](../src/render/raster.c#L521) |
| `0x81c14fb8` | [`sango_bitmap_draw_frame_screen`](../src/render/raster.c#L529) |
| `0x81c15070` | [`sango_bitmap_draw_frame`](../src/render/raster.c#L566) |
| `0x81c15134` | [`sango_text_draw_context`](../src/render/raster.c#L608) |
| `0x81c151a8` | [`sango_text_reset_clip_bounds`](../src/render/raster.c#L616) |
| `0x81c151e4` | [`sango_text_draw_character`](../src/render/raster.c#L629) |
| `0x81c15210` | [`sango_render_clear_rectangle`](../src/render/raster.c#L637) |
| `0x81c152a4` | [`sango_bitmap_rectangle_byte_count`](../src/render/raster.c#L649) |

## src/resources/library.c

索引资源读取、文字解码和诊断显示。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c152f0` | [`sango_resource_item`](../src/resources/library.c#L7) |
| `0x81c153d8` | [`sango_resource_offset`](../src/resources/library.c#L65) |
| `0x81c15428` | [`sango_resource_item_size`](../src/resources/library.c#L84) |
| `0x81c154d8` | [`sango_resource_read_text`](../src/resources/library.c#L122) |
| `0x81c155e4` | [`sango_resource_decode_bytes`](../src/resources/library.c#L180) |
| `0x81c156e0` | [`sango_debug_draw_integer`](../src/resources/library.c#L199) |
| `0x81c15834` | [`sango_debug_show_resource_id`](../src/resources/library.c#L261) |

## src/ui/start_menu.c

初始会话、主菜单、剧本和君主选择。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c159a0` | [`sango_allocate_session_state`](../src/ui/start_menu.c#L6) |
| `0x81c15acc` | [`sango_select_session`](../src/ui/start_menu.c#L52) |
| `0x81c15d18` | [`sango_menu_select_animated`](../src/ui/start_menu.c#L160) |
| `0x81c15e44` | [`sango_menu_show_credits`](../src/ui/start_menu.c#L236) |
| `0x81c15e6c` | [`sango_menu_choose_ruler`](../src/ui/start_menu.c#L244) |
| `0x81c161c4` | [`sango_menu_flash_ruler_cities`](../src/ui/start_menu.c#L339) |
| `0x81c16274` | [`sango_menu_draw_ruler_names`](../src/ui/start_menu.c#L347) |
| `0x81c162e0` | [`sango_animation_play_resource`](../src/ui/start_menu.c#L354) |

## src/save/savegame.c

三个存档槽、双文件读取与写入。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c16330` | [`sango_save_choose_slot`](../src/save/savegame.c#L7) |
| `0x81c164c8` | [`sango_save_draw_slots`](../src/save/savegame.c#L89) |
| `0x81c16704` | [`sango_save_load_slot`](../src/save/savegame.c#L175) |
| `0x81c16940` | [`sango_save_write_slot`](../src/save/savegame.c#L223) |

## src/app/lifecycle.c

应用及游戏会话总流程。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c16c24` | [`sango_main`](../src/app/lifecycle.c#L6) |
| `0x81c16c80` | [`sango_game_lifecycle`](../src/app/lifecycle.c#L21) |
| `0x81c16d68` | [`sango_app_free_resource_buffer`](../src/app/lifecycle.c#L68) |
| `0x81c16db0` | [`sango_app_show_initialization_error`](../src/app/lifecycle.c#L78) |
| `0x81c16de8` | [`sango_resource_prepare_hook`](../src/app/lifecycle.c#L90) |

## src/strategy/calendar.c

城市月度事件与年度武将更新。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c16e00` | [`sango_strategy_apply_monthly_economy`](../src/strategy/calendar.c#L6) |
| `0x81c171cc` | [`sango_strategy_apply_city_disasters`](../src/strategy/calendar.c#L171) |
| `0x81c1740c` | [`sango_strategy_apply_disaster_losses`](../src/strategy/calendar.c#L281) |
| `0x81c1767c` | [`sango_strategy_collect_commerce_income`](../src/strategy/calendar.c#L350) |
| `0x81c176d8` | [`sango_strategy_collect_agriculture_income`](../src/strategy/calendar.c#L374) |
| `0x81c17734` | [`sango_strategy_update_character_ages_and_debut`](../src/strategy/calendar.c#L398) |

## src/strategy/items.c

宝物装备属性修改和数量统计。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c17a08` | [`sango_item_apply_attributes`](../src/strategy/items.c#L6) |
| `0x81c17b3c` | [`sango_faction_count_characters`](../src/strategy/items.c#L56) |

## src/ui/info_panels.c

城市事件、武将提示、宝物出现与属性消息。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c17c48` | [`sango_ui_show_city_event`](../src/ui/info_panels.c#L6) |
| `0x81c17e18` | [`sango_strategy_spawn_items_for_year`](../src/ui/info_panels.c#L61) |
| `0x81c17eb4` | [`sango_item_remove_attributes`](../src/ui/info_panels.c#L87) |
| `0x81c17f44` | [`sango_ui_show_strategy_text`](../src/ui/info_panels.c#L106) |
| `0x81c17f78` | [`sango_ui_draw_character_panel`](../src/ui/info_panels.c#L118) |
| `0x81c18024` | [`sango_ui_show_character_message`](../src/ui/info_panels.c#L135) |
| `0x81c18150` | [`sango_item_mark_discovered`](../src/ui/info_panels.c#L166) |
| `0x81c181b8` | [`sango_city_list_items`](../src/ui/info_panels.c#L193) |
| `0x81c18248` | [`sango_city_find_item`](../src/ui/info_panels.c#L227) |
| `0x81c182d0` | [`sango_city_neighbor_direction`](../src/ui/info_panels.c#L261) |

## src/ui/lists.c

分页表格、宝物及武将列表。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c18350` | [`sango_ui_table_begin`](../src/ui/lists.c#L6) |
| `0x81c18380` | [`sango_ui_table_next_cell`](../src/ui/lists.c#L26) |
| `0x81c18410` | [`sango_ui_table_next_row`](../src/ui/lists.c#L62) |
| `0x81c18450` | [`sango_ui_draw_item_row`](../src/ui/lists.c#L78) |
| `0x81c185cc` | [`sango_item_format_attribute`](../src/ui/lists.c#L127) |
| `0x81c18704` | [`sango_ui_draw_item_header`](../src/ui/lists.c#L188) |
| `0x81c18874` | [`sango_ui_select_item`](../src/ui/lists.c#L236) |
| `0x81c18c80` | [`sango_item_read_name`](../src/ui/lists.c#L399) |
| `0x81c18cac` | [`sango_ui_draw_character_row`](../src/ui/lists.c#L406) |
| `0x81c18e88` | [`sango_character_format_attribute`](../src/ui/lists.c#L476) |
| `0x81c19100` | [`sango_ui_draw_character_header`](../src/ui/lists.c#L619) |
| `0x81c19270` | [`sango_ui_select_character`](../src/ui/lists.c#L668) |

## src/ui/city_details.c

城市名称、属性面板和城市命令入口。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c1971c` | [`sango_city_read_name`](../src/ui/city_details.c#L6) |
| `0x81c19748` | [`sango_city_format_attribute`](../src/ui/city_details.c#L13) |
| `0x81c19a98` | [`sango_city_format_status`](../src/ui/city_details.c#L133) |
| `0x81c19b1c` | [`sango_ui_show_city_details`](../src/ui/city_details.c#L158) |
| `0x81c19cac` | [`sango_load_named_text`](../src/ui/city_details.c#L239) |
| `0x81c19d30` | [`sango_strategy_run_player_commands`](../src/ui/city_details.c#L267) |

## src/strategy/ai.c

电脑城市的内政、外交和军事决策。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c19df8` | [`sango_strategy_run_city_ai`](../src/strategy/ai.c#L6) |
| `0x81c19f8c` | [`sango_strategy_ai_domestic_actions`](../src/strategy/ai.c#L71) |
| `0x81c1a188` | [`sango_strategy_ai_diplomacy_actions`](../src/strategy/ai.c#L175) |
| `0x81c1a480` | [`sango_strategy_ai_city_events`](../src/strategy/ai.c#L346) |
| `0x81c1a6a4` | [`sango_strategy_ai_military_actions`](../src/strategy/ai.c#L447) |

## src/strategy/turns.c

战略月份推进、城池汇总和剧本初始化。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c1aab4` | [`sango_strategy_run_months`](../src/strategy/turns.c#L7) |
| `0x81c1abd4` | [`sango_strategy_player_is_only_ruler`](../src/strategy/turns.c#L59) |
| `0x81c1ac04` | [`sango_strategy_player_has_no_cities`](../src/strategy/turns.c#L69) |
| `0x81c1ac34` | [`sango_strategy_refresh_city_governors`](../src/strategy/turns.c#L79) |
| `0x81c1ad30` | [`sango_scenario_collect_rulers`](../src/strategy/turns.c#L147) |
| `0x81c1add4` | [`sango_scenario_initialize`](../src/strategy/turns.c#L199) |

## src/ui/system_menu.c

系统菜单、数值选择及电脑执行提示。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c1b2b4` | [`sango_ui_show_system_menu`](../src/ui/system_menu.c#L6) |
| `0x81c1b364` | [`sango_ui_select_number`](../src/ui/system_menu.c#L44) |
| `0x81c1b784` | [`sango_ui_show_ai_progress`](../src/ui/system_menu.c#L179) |

## src/strategy/session.c

月末事件及剧本加载包装。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c1b89c` | [`sango_strategy_apply_calendar_events`](../src/strategy/session.c#L6) |
| `0x81c1b91c` | [`sango_scenario_load`](../src/strategy/session.c#L23) |

## src/runtime/strings.c

恢复的字符串与基础格式化运行库。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c1b950` | [`sango_crt_memchr`](../src/runtime/strings.c#L6) |
| `0x81c1b980` | [`sango_crt_sprintf_words`](../src/runtime/strings.c#L26) |
| `0x81c1b9d4` | [`sango_crt_strlen`](../src/runtime/strings.c#L49) |
| `0x81c1ba04` | [`sango_crt_strtol`](../src/runtime/strings.c#L68) |
| `0x81c1bc58` | [`sango_crt_atoi_compat`](../src/runtime/strings.c#L166) |
| `0x81c1bcbc` | [`sango_crt_strcpy`](../src/runtime/strings.c#L173) |
| `0x81c1bce0` | [`crt_memset`](../src/runtime/strings.c#L190) |
| `0x81c1bd08` | [`crt_memcpy`](../src/runtime/strings.c#L205) |
| `0x81c1bd3c` | [`sango_crt_stub_1bd3c`](../src/runtime/strings.c#L224) |
| `0x81c1bd48` | [`sango_crt_stub_1bd48`](../src/runtime/strings.c#L230) |
| `0x81c1bd50` | [`sango_crt_vformat`](../src/runtime/strings.c#L236) |

## src/runtime/format.c

恢复的数值格式化和浮点文本转换。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c1c48c` | [`sango_crt_append_character`](../src/runtime/format.c#L6) |
| `0x81c1c4a0` | [`sango_crt_initialize`](../src/runtime/format.c#L17) |
| `0x81c1c540` | [`sango_crt_read_buffer`](../src/runtime/format.c#L39) |
| `0x81c1c5d8` | [`sango_crt_abort_loop`](../src/runtime/format.c#L65) |
| `0x81c1c5e0` | [`sango_crt_reset_input_buffer`](../src/runtime/format.c#L74) |
| `0x81c1c5f4` | [`crt_diagnostic_noop`](../src/runtime/format.c#L82) |
| `0x81c1c600` | [`sango_crt_isdigit`](../src/runtime/format.c#L88) |
| `0x81c1c620` | [`sango_crt_isspace`](../src/runtime/format.c#L101) |
| `0x81c1c650` | [`sango_crt_toupper`](../src/runtime/format.c#L116) |
| `0x81c1c670` | [`sango_crt_format_entry`](../src/runtime/format.c#L131) |
| `0x81c1c6d0` | [`sango_crt_format_words`](../src/runtime/format.c#L156) |
| `0x81c1ce34` | [`sango_crt_format_field`](../src/runtime/format.c#L565) |
| `0x81c1d198` | [`sango_crt_format_unsigned_digits`](../src/runtime/format.c#L746) |
| `0x81c1d2d4` | [`sango_crt_format_double_digits`](../src/runtime/format.c#L822) |
| `0x81c1da28` | [`sango_crt_scale_double_decimal`](../src/runtime/format.c#L1113) |

## src/runtime/libc.c

恢复的整数转换、随机数及字符串辅助。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c1dc10` | [`sango_crt_heap_allocate`](../src/runtime/libc.c#L6) |
| `0x81c1dd88` | [`sango_crt_heap_initialize`](../src/runtime/libc.c#L68) |
| `0x81c1de00` | [`sango_crt_abs`](../src/runtime/libc.c#L90) |
| `0x81c1de20` | [`crt_rand`](../src/runtime/libc.c#L100) |
| `0x81c1de60` | [`crt_srand`](../src/runtime/libc.c#L107) |
| `0x81c1de70` | [`sango_crt_strcat`](../src/runtime/libc.c#L114) |
| `0x81c1deb0` | [`sango_crt_heap_shift_forward`](../src/runtime/libc.c#L138) |
| `0x81c1dee0` | [`sango_crt_zero_bytes`](../src/runtime/libc.c#L157) |
| `0x81c1df08` | [`sango_crt_heap_shift_backward`](../src/runtime/libc.c#L177) |

## src/runtime/soft_float.c

恢复的IEEE754软件浮点实现。

| 原地址 | 当前函数／源码位置 |
| --- | --- |
| `0x81c1df40` | [`sango_soft_f32_to_int`](../src/runtime/soft_float.c#L6) |
| `0x81c1dfb0` | [`sango_soft_add_f32_parts`](../src/runtime/soft_float.c#L26) |
| `0x81c1e1ec` | [`soft_float_add`](../src/runtime/soft_float.c#L182) |
| `0x81c1e24c` | [`soft_float_sub`](../src/runtime/soft_float.c#L209) |
| `0x81c1e2c0` | [`soft_float_mul`](../src/runtime/soft_float.c#L239) |
| `0x81c1e4b0` | [`soft_float_div`](../src/runtime/soft_float.c#L355) |
| `0x81c1e620` | [`sango_soft_compare_f32`](../src/runtime/soft_float.c#L449) |
| `0x81c1e6b0` | [`sango_soft_int_to_f32`](../src/runtime/soft_float.c#L476) |
| `0x81c1e770` | [`sango_soft_unpack_f32_integer`](../src/runtime/soft_float.c#L523) |
| `0x81c1e810` | [`sango_soft_add_f64_parts`](../src/runtime/soft_float.c#L567) |
| `0x81c1eb70` | [`sango_soft_add_f64`](../src/runtime/soft_float.c#L757) |
| `0x81c1ebd8` | [`sango_soft_sub_f64`](../src/runtime/soft_float.c#L791) |
| `0x81c1ec50` | [`sango_soft_mul_f64`](../src/runtime/soft_float.c#L828) |
| `0x81c1efe0` | [`sango_soft_div_f64`](../src/runtime/soft_float.c#L997) |
| `0x81c1f210` | [`sango_soft_compare_f64_nan_high`](../src/runtime/soft_float.c#L1123) |
| `0x81c1f2a0` | [`sango_soft_compare_f64_nan_low`](../src/runtime/soft_float.c#L1157) |
| `0x81c1f330` | [`sango_soft_compare_f64_nan_low_compat`](../src/runtime/soft_float.c#L1191) |
| `0x81c1f3c0` | [`sango_soft_compare_f64_nan_high_compat`](../src/runtime/soft_float.c#L1225) |
| `0x81c1f450` | [`sango_soft_int_to_f64`](../src/runtime/soft_float.c#L1259) |
| `0x81c1f540` | [`sango_soft_f64_to_int`](../src/runtime/soft_float.c#L1313) |
| `0x81c1f620` | [`sango_soft_pack_f32`](../src/runtime/soft_float.c#L1376) |
| `0x81c1f790` | [`sango_soft_unpack_f32`](../src/runtime/soft_float.c#L1461) |
| `0x81c1f860` | [`sango_soft_compare_f32_parts`](../src/runtime/soft_float.c#L1523) |
| `0x81c1f9a0` | [`sango_soft_pack_f64`](../src/runtime/soft_float.c#L1600) |
| `0x81c1fc40` | [`sango_soft_unpack_f64`](../src/runtime/soft_float.c#L1718) |
| `0x81c1fd60` | [`sango_soft_compare_f64_parts`](../src/runtime/soft_float.c#L1786) |
