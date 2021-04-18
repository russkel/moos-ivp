;*****************************************************************;
;*    NAME: Jacob Gerlach and Michael Benjamin                   *;
;*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     *;
;*    FILE: moos-apps.el                                         *;
;*    DATE: April 27th 2014                                      *;
;*                                                               *;
;* This file is part of MOOS-IvP                                 *;
;*                                                               *;
;* MOOS-IvP is free software: you can redistribute it and/or     *;
;* modify it under the terms of the GNU General Public License   *;
;* as published by the Free Software Foundation, either version  *;
;* 3 of the License, or (at your option) any later version.      *;
;*                                                               *;
;* MOOS-IvP is distributed in the hope that it will be useful,   *;
;* but WITHOUT ANY WARRANTY; without even the implied warranty   *;
;* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See  *;
;* the GNU General Public License for more details.              *;
;*                                                               *;
;* You should have received a copy of the GNU General Public     *;
;* License along with MOOS-IvP.  If not, see                     *;
;* <http://www.gnu.org/licenses/>.                               *;
;*****************************************************************;

(setq moos-app-and-keyword-list
      (list
      '("ANTLER" "MSBetweenLaunches" "Run" "NewConsole")
      '("iM300" "comms_type" "port" "ip_addr" "stale_thresh" "max_rudder" "max_thrust" "drive_mode" "max_appcast_events")
      '("uSockComms" "comms_type" "port" "ip_addr" "max_appcast_events")
      '("uSimTowBody" "tow_cable_length" "tow_body_length" "swath_width" "swath_length" "swath_color" "swath_transparency" "max_appcast_events" )
      '("uSimWaterway" "border" "cover_poly" "cell_size" "cell_val" "max_appcast_events" )
      '("pMissionEval" "lead_condition" "pass_condition" "fail_condition" "result_flag" "pass_flag" "fail_flag"  "max_appcast_events")
      '("uFldVoronoi" "stale_time" "verbose" "region" "max_appcast_events")
      '("pRealm" "relcast_interval" "summary_interval" "wrap_length" "trunc_length" "msg_max_hist" "hist_var" "scope_set" "max_appcast_events" "msg_max_history")
      '("uSimHeron" "port" "comms_type" "ip_addr" "max_appcast_events")
      '("uFldVoronoi" "reject_range" "post_poly" "post_region" "region" "max_appcast_events")
      '("uMemWatch" "ignore" "watch_only" "absolute_time_gap" "max_appcast_events")
      '("uFldCollObDetect" "collision_dist" "near_miss_dist" "encounter_dist" "collision_range" "near_miss_range" "encounter_range" "collision_flag" "near_miss_flag" "encounter_flag" "ignore_group" "reject_group" "max_appcast_events")
      '("uFldObstacleSim" "obstacle_file" "poly_vert_color" "poly_edge_color" "poly_fill_color" "poly_label_color" "poly_vert_size" "poly_edge_size" "draw_region" "post_points" "rate_points" "poly_transparency" "region_edge_color" "min_duration" "max_duration" "reuse_ids" "reset_interval" "reset_range" "refresh_interval" "max_appcast_events" "point_size")
      '("uFldWrapDetect" "max_segments" "max_trail_distance" "max_trail_dist" "max_appcast_events")
      '("pMovingSurvey" "survey" "heading" "speed" "reverse_interval" "update_interval" "rpm" "max_appcast_events")
      '("pHostInfoV2" "prefer_hostip" "backup_hostip" "max_appcast_events")
      
      '("uTimerScript" "event" "paused" "reset_max" "reset_time" "delay_reset" "condition" "delay_start" "forward_var" "pause_var" "rand_var" "randvar" "reset_var" "script_atomic" "script_name" "shuffle" "verbose" "upon_awake" "status_var" "time_warp" "time_zero" "pause_variable" "forward_variable" "max_appcast_events" "block_on")
      '("uProcessWatch"  "watch" "watch_all" "nowatch" "allow_retractions" "summary_wait" "post_mapping" "max_appcast_events")
      '("uSimMarine"  "start_x" "start_y" "start_heading" "start_speed" "start_depth" "start_pos" "drift_x" "drift_y" "rotate_speed" "drift_vector" "buoyancy_rate" "max_acceleration" "max_deceleration" "max_depth_rate" "max_depth_rate_speed" "sim_pause" "dual_state" "thrust_reflect" "thrust_factor" "turn_rate" "thrust_map" "prefix" "default_water_depth" "trim_tolerance" "max_trim_delay" "max_rudder_degs_per_sec" "max_appcast_events")
      '("uSimMarineTow" "tow_dist" "lead_vname" "enabled_flag" "disabled_flag" "max_appcast_events") 
      '("uSimMarineX"  "start_x" "start_y" "start_heading" "start_speed" "start_depth" "start_pos" "drift_x" "drift_y" "rotate_speed" "drift_vector" "buoyancy_rate" "max_acceleration" "max_deceleration" "max_depth_rate" "max_depth_rate_speed" "sim_pause" "dual_state" "thrust_reflect" "thrust_factor" "turn_rate" "thrust_map" "prefix" "default_water_depth" "trim_tolerance" "max_trim_delay" "max_rudder_degs_per_sec" "wormhole" "depth_control" "yaw_pid_kp" "yaw_pid_kd" "yaw_pid_ki" "yaw_pid_integral_limit" "speed_pid_kp" "speed_pid_kd" "speed_pid_ki" "speed_pid_integral_limit" "maxrudder" "maxthrust" "speed_factor"  "max_appcast_events")
      '("pHelmIvP" "term_report_interval" "ivp_behavior_dir" "behaviors" "domain" "start_engaged" "allow_disengaged" "disengage_on_allstop" "other_override_var" "node_skew" "ok_skew" "verbose" "bhv_dir_not_found_ok" "start_in_drive" "kcache" "hold_on_apps" "max_appcast_events")
      '("pMarinePID" "speed_factor" "sim_instability" "tardy_helm_threshold" "tardy_nav_threshold" "active_start" "verbose" "yaw_pid_kp" "yaw_pid_kd" "yaw_pid_ki" "yaw_pid_integral_limit" "yaw_pid_ki_limit" "maxrudder" "speed_pid_" "speed_pid_kp" "speed_pid_kd" "speed_pid_ki" "speed_pid_integral_limit" "maxthrust" "depth_control" "z_to_pitch_pid_kp" "z_to_pitch_pid_kd" "z_to_pitch_pid_ki" "z_to_pitch_pid_integral_limit" "maxpitch" "pitch_pid_kp" "pitch_pid_kd" "pitch_pid_ki" "pitch_pid_integral_limit" "maxelevator" "max_appcast_events")
      '("uTermCommand" "cmd")
      '("pNodeReporter" "platform_type" "platform_length" "blackout_interval" "plat_report_input" "plat_report_output" "node_report_output" "nohelm_threshold" "crossfill_policy" "alt_nav_prefix" "alt_nav_name" "vessel_type" "group" "paused" "terse_reports" "platform_color" "max_appcast_events")

      '("pMarineViewer" "tiff_file" "tiff_file_b" "set_pan_x" "set_pan_y" "zoom" "center_view" "vehicle_shape_scale" "hash_delta" "hash_shade" "hash_viewable" "full_screen" "polygon_viewable_all" "polygon_viewable_labels" "seglist_viewable_all" "seglist_viewable_labels" "point_viewable_all" "point_viewable_labels" "vector_viewable_all" "vector_viewable_labels" "circle_viewable_all" "circle_viewable_labels" "grid_viewable_all" "grid_viewable_labels" "grid_opaqueness" "datum_viewable_all" "datum_viewable_labels" "marker_viewable_all" "marker_viewable_labels" "oparea_viewable_all" "oparea_viewable_labels" "drop_point_viewable_all" "drop_point_coords" "drop_point_vertex_size" "range_pulse_viewable_all" "comms_pulse_viewable_all" "vehicles_viewable" "vehicles_name_mode" "stale_report_thresh" "stale_remove_thresh" "vehicles_active_color" "vehicles_inactive_color" "trails_viewable" "trails_color" "trails_point_size" "bearing_lines" "appcast_viewable" "refresh_mode" "nodes_font_size" "procs_font_size" "infocast_font_size" "appcast_font_size" "appcast_color_scheme" "appcast_width" "appcast_height" "scope" "action" "action+" "button_one" "button_two" "button_three" "button_four" "button_five" "button_six" "button_seven" "button_eight" "button_nine" "button_ten" "button_eleven" "button_twelve" "button_thirteen" "button_fourteen" "button_fifteen" "button_sixteen" "button_seventeen" "button_eighteen" "button_nineteen" "button_twenty" "button_1" "button_2" "button_3" "button_4" "button_5" "button_6" "button_7" "button_8" "button_9" "button_10" "button_11" "button_12" "button_13" "button_14" "button_15" "button_16" "button_17" "button_18" "button_19" "button_20" "op_vertex" "marker" "marker_scale" "vehicles_shape_scale" "vcolor" "cmd" "node_pulse_viewable_all" "watch_cluster" "content_mode" "realmcast_channel" "infocast_viewable" "max_appcast_events")

      '("uFldContactRangeSensor" "push_distance" "pull_distance" "push_dist" "pull_dist" "ping_wait" "report_vars" "ground_truth" "verbose" "display_pulses" "ping_color" "echo_color" "reply_color" "allow_echo_types" "rn_uniform_pct" "rn_gaussian_sigma" "sensor_arc" "max_appcast_events")
      '("uFldNodeComms" "comms_range" "critical_range" "stale_time" "min_msg_interval" "max_msg_length" "view_node_rpt_pulses" "verbose" "stealth" "earange" "groups" "min_rpt_interval" "pulse_duration" "drop_percentage" "max_appcast_events")
      '("uFldFlagManager" "flag" "grabbed_color" "ungrabbed_color" "default_flag_type" "default_flag_width" "default_flag_range" "grab_post" "near_post" "away_post" "deny_post" "goal_post" "home_post" "max_appcast_events")
      '("uDialogManager" "nickname")
      '("uFunctionVis")
      '("uSpeechRec" "juliuscof")
      '("uFldTagManager" "tag_range" "tag_min_interval" "post_color" "hit_color" "miss_color" "zone_one" "zone_two" "team_one" "team_two" "robot_tag_post" "human_tag_post" "human_untag_post" "robot_untag_post" "tag_circle" "tag_circle_color" "tag_circle_range" "zone_one_color" "zone_two_color" "tag_duration" "notag_post" "max_appcast_events")
      '("uFldShoreBroker" "warning_on_stale" "bridge" "qbridge" "auto_bridge_realmcast" "auto_bridge_appcast"  "max_appcast_events")
      '("uCommand" "cmd")
      '("uFldNodeBroker" "keyword" "try_shore_host" "bridge"  "auto_bridge_realmcast" "auto_bridge_appcast"  "max_appcast_events")
      '("pHostInfo" "temp_file_dir" "default_hostip" "default_hostip_force")
      '("pEchoVar" "flip:1" "flip:2" "condition" "hold_messages" "max_appcast_events")
      '("pSearchGrid" "grid_config" "max_appcast_events")
      '("uPlotViewer" "plot_var")
      '("iM200" "thrust_mode" "ip_address" "port_number" "heading_source" "heading_msg_name" "mag_offset")
      '("pObstacleMgr" "point_var" "obstacles_color" "given_obstacle" "post_dist_to_polys" "post_view_polys" "max_pts_per_cluster" "max_age_per_point" "alert_range" "ignore_range" "lasso" "lasso_points" "lasso_radius" "obstacles_color" "poly_label_thresh" "poly_shade_thresh" "poly_vertex_thresh" "given_max_duration" "max_appcast_events" "new_obs_flag")
      '("pPoseKeep" "hold_tolerance" "hold_duration" "endflag" "hold_heading")
      '("uFldHazardSensor" "term_report_interval" "max_appcast_events" "max_appcast_run_warnings" "default_hazard_shape" "default_hazard_color" "default_hazard_width" "default_benign_shape" "default_benign_color" "default_benign_width" "swath_transparency" "sensor_config" "hazard_file" "swath_length" "seed_random" "show_hazards" "show_swath" "show_detections" "show_reports" "show_pd" "show_pfa" "min_reset_interval" "min_classify_interval" "options_summary_interval")
      '("uFldHazardMgr" "swath_width" "sensor_pd" "report_name" "region" "pd" "max_appcast_events")
      '("uFldHazardMetric" "penalty_missed_hazard" "penalty_false_alarm" "penalty_max_time_over" "penalty_max_time_rate" "max_time" "hazard_file" "show_xpath" "max_appcast_events")
      '("uFldMessageHandler" "strict_addressing" "max_appcast_events")
      '("uMACView" "procs_font_size" "nodes_font_size" "appcast_font_size" "appcast_color_scheme" "appcast_height" "refresh_mode" "content_mode" "watch_cluster" "realmcast_channel")
      '("uMAC")
      '("pDeadManPost" "heartbeat_var" "max_noheart" "deadflag" "post_policy" "active_at_start" "max_appcast_events")
      '("pRangeEvent" "min_range" "max_range" "event_var" "ignore_group" "max_appcast_events")
      '("uPokeDB")
      '("uQueryDB" "max_time" "halt_max_time" "condition" "halt_condition" "pass_condition" "fail_condition" "check_var")
      '("uHelmScope" "paused" "display_moos_scope" "display_bhv_posts" "display_virgins" "truncated_output" "behaviors_consise" "var")
      '("pSafetyRetreat" "polygon" "duration" "retreat_cue" "retreat_message_var" "retreat_notify_var" "verbose" "retreat_cue_var")
      '("uFldBeaconRangeSensor" "reach_distance" "reach_distance" "ping_wait" "ping_wait" "ping_payments" "report_vars" "ground_truth" "verbose" "default_beacon_shape" "default" "default_beacon_width" "default_beacon_report_range" "default_beacon_freq" "beacon" "beacon" "beacon" "rn_algorithm" "default_beacon_color" "default_beacon_push_dist" "default_beacon_pull_dist" "node_push_dist" "node_pull_dist")
      '("uFldPathCheck" "history_length")
      '("pShare" "input" "output" "" "" "" "")
      '("pBasicContactMgr" "alert" "alert_range_color" "cpa_range_color" "contact_max_age" "display_radii" "display_radii_id" "alert_verbose" "decay" "contacts_recap_interval" "contact_local_coords" "ignore_group" "ignore_type" "match_type" "match_group" "match_region" "ignore_region" "strict_ignore" "range_report_timeout" "post_closest_range" "max_retired_history" "reject_range" "contact_max_age" "eval_range_far" "eval_range_near" "max_appcast_events")
      '("pContactMgrV20" "alert" "alert_range_color" "cpa_range_color" "contact_max_age" "display_radii" "display_radii_id" "alert_verbose" "decay" "recap_interval" "contact_local_coords" "ignore_group" "ignore_type" "match_type" "match_group" "match_region" "ignore_region" "strict_ignore" "range_report_timeout" "post_closest_range" "max_retired_history" "reject_range" "contact_max_age" "eval_range_far" "eval_range_near" "max_appcast_events")

      '("uLoadWatch" "thresh" "breach_trigger" "max_appcast_events")
      '("uSimLidar" "poly" "polygon" "max_range" "mount_angle" "point_cloud_color" "range" "beams" "field_of_view" "scan_resolution" "max_appcast_events")
      '("iSay" "default_voice" "default_rate" "interval_policy" "min_utter_interval" "audio_dir" "os_mode" "max_appcast_events")
      '("uXMS" "var" "source" "history_var" "display_virgins" "display_source" "display_aux_source" "display_time" "display_community" "display_all" "trunc_data" "term_report_interval" "colormap" "color_map" "refresh_mode" "content_mode" "paused")
      '("uSimCurrent" "current_field")

      '("pEvalLoiter" "eval_window" "nav_stale_thresh" "mode_thresh" "max_nav_age" "range_max_ineff" "notable_cpa_thresh" "notable_eff_thresh" "notable_cpa_var" "notable_eff_var" "max_appcast_events")
      
      '("uFldSwarmAssign" "task")
      '("pProxonoi" "region" "max_appcast_events")
      '("uFldCollisionDetect" "collision_range" "collision_dist" "near_miss_range" "near_miss_range" "pulse_render" "pulse_range" "pulse_duration" "condition" "collision_flag" "near_miss_flag" "encounter_flag" "encounter_range" "encounter_dist" "report_all_encounters" "max_appcast_events")

      '("pPolePath" "start_line" "end_line" "poles_number" "steps_number" "display_poles" "display_steps" "start_pole" "output_var" "random_end")
      '("pRangeSensorHangler" "local_range" "range_report" "target_name" "verbose" "disp_range_circle" "max_appcast_events")
      '("uFldDepthChargeMgr" "depth_charge_config" "depth_charge_range_default" "depth_charge_amount_default" "depth_charge_delay_default" "depth_charge_delay_max" "replenish_range" "replenish_time" "replenish_station" "visual_hints" "max_appcast_events")

      '("uFldProtocolEval" "collision_range" "near_miss_range" "cpa_violation_range" "detection_range" "preferred_cpa_range" "time_threshold" "report_threshold" "delay_time_to_clear" "deploy_delay_time" "pulse" "pulse_range" "pulse_duration" "vtype" "drop_track_range" "colregs_report_threshold" "safety_report_threshold" "max_time_between_reports" "sound_collision" "sound_near_miss" "sound_cpa_violation" "sound_rule_violation" "r14_penalty_function" "r14_max_course_penalty" "verbose")

      '("uScoreKeeper" "target_name" "hit_award" "miss_penalty" "range_dist")
      '("pParticleFilter" "range_report" "target_name" "my_contact" "partical_count" "no_parts" "n_threshold" "reserve_parts" "parts_disp_tick" "max_speed" "speed_noise" "course_noise" "range_var" "ceiling" "verbose" "particle_color")

      '("pEncircle" "circle_position" "max_speed" "aggression" "encircle_active" "consider_thresh" "on_circle_thres" "message_color" "max_appcast_events")
      
       '("pTaskManager" "max_appcast_events")
       '("uFldTaskMonitor")

      '("pTowManager" "ownship"  "max_appcast_events")
      
      '("pLogger" "AsyncLog" "WildCardLogging" "Log" "LogAuxSrc" "WildCardExclusionLog" "WildCardOmitPattern" "file" "path" "synclog" "filetimestamp" "LoggingDirectorySummaryFile"  "UTCLogDirectories" "DoublePrecision" "MarkExternalCommunityMessages" "MarkDataType" "CompressAlogs" "file")))

