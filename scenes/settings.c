#include "../tesla_fsd_app.h"
#include "../scenes_config/app_scene_functions.h"

static const char* const toggle_text[] = {"OFF", "ON"};

static void force_fsd_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->force_fsd = (idx == 1);
}

static void chime_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->suppress_speed_chime = (idx == 1);
}

static void emerg_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->emergency_vehicle_detect = (idx == 1);
}

static void nag_killer_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->nag_killer = (idx == 1);
}

static const char* const op_mode_text[] = {"Active", "Listen", "Service"};
static void op_mode_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, op_mode_text[idx]);
    app->op_mode = (OpMode)idx;
}

static void shield_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->gtw_shield = (idx == 1);
}

static void tlssc_restore_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->tlssc_restore = (idx == 1);
}

static void tier_override_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->gtw_tier_override = (idx == 1);
}

static void nav_enable_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->assist_nav_enable = (idx == 1);
}

static void hands_off_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->assist_hands_off = (idx == 1);
}

static void dev_mode_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->assist_dev_mode = (idx == 1);
}

static void lhd_override_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->assist_lhd_override = (idx == 1);
}

static void lane_graph_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->assist_show_lane_graph = (idx == 1);
}

static void tlssc_bit38_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->assist_tlssc_bit38 = (idx == 1);
}

static const char* const clock_text[] = {"16 MHz", "8 MHz", "12 MHz"};
static void clock_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, clock_text[idx]);
    app->mcp_clock = idx;
}

static void precondition_changed(VariableItem* item) {
    TeslaFSDApp* app = variable_item_get_context(item);
    uint8_t idx = variable_item_get_current_value_index(item);
    variable_item_set_current_value_text(item, toggle_text[idx]);
    app->precondition = (idx == 1);
}

void tesla_fsd_scene_settings_on_enter(void* context) {
    TeslaFSDApp* app = context;
    VariableItemList* list = app->var_item_list;
    variable_item_list_reset(list);

    VariableItem* item;

    item = variable_item_list_add(list, "Force FSD", 2, force_fsd_changed, app);
    variable_item_set_current_value_index(item, app->force_fsd ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->force_fsd ? 1 : 0]);

    item = variable_item_list_add(list, "Suppress Chime", 2, chime_changed, app);
    variable_item_set_current_value_index(item, app->suppress_speed_chime ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->suppress_speed_chime ? 1 : 0]);

    item = variable_item_list_add(list, "Emerg. Vehicle", 2, emerg_changed, app);
    variable_item_set_current_value_index(item, app->emergency_vehicle_detect ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->emergency_vehicle_detect ? 1 : 0]);

    item = variable_item_list_add(list, "Nag Killer", 2, nag_killer_changed, app);
    variable_item_set_current_value_index(item, app->nag_killer ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->nag_killer ? 1 : 0]);

    item = variable_item_list_add(list, "Mode", 3, op_mode_changed, app);
    variable_item_set_current_value_index(item, (uint8_t)app->op_mode);
    variable_item_set_current_value_text(item, op_mode_text[(uint8_t)app->op_mode]);

    item = variable_item_list_add(list, "Precondition", 2, precondition_changed, app);
    variable_item_set_current_value_index(item, app->precondition ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->precondition ? 1 : 0]);

    item = variable_item_list_add(list, "Ban Shield", 2, shield_changed, app);
    variable_item_set_current_value_index(item, app->gtw_shield ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->gtw_shield ? 1 : 0]);

    item = variable_item_list_add(list, "TLSSC Restore", 2, tlssc_restore_changed, app);
    variable_item_set_current_value_index(item, app->tlssc_restore ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->tlssc_restore ? 1 : 0]);

    item = variable_item_list_add(list, "Tier Override", 2, tier_override_changed, app);
    variable_item_set_current_value_index(item, app->gtw_tier_override ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->gtw_tier_override ? 1 : 0]);

    item = variable_item_list_add(list, "Nav FSD Route", 2, nav_enable_changed, app);
    variable_item_set_current_value_index(item, app->assist_nav_enable ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->assist_nav_enable ? 1 : 0]);

    item = variable_item_list_add(list, "Hands-Off (UI)", 2, hands_off_changed, app);
    variable_item_set_current_value_index(item, app->assist_hands_off ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->assist_hands_off ? 1 : 0]);

    item = variable_item_list_add(list, "Dev Mode", 2, dev_mode_changed, app);
    variable_item_set_current_value_index(item, app->assist_dev_mode ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->assist_dev_mode ? 1 : 0]);

    item = variable_item_list_add(list, "Force LHD", 2, lhd_override_changed, app);
    variable_item_set_current_value_index(item, app->assist_lhd_override ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->assist_lhd_override ? 1 : 0]);

    item = variable_item_list_add(list, "Lane Graph", 2, lane_graph_changed, app);
    variable_item_set_current_value_index(item, app->assist_show_lane_graph ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->assist_show_lane_graph ? 1 : 0]);

    item = variable_item_list_add(list, "TLSSC bit38", 2, tlssc_bit38_changed, app);
    variable_item_set_current_value_index(item, app->assist_tlssc_bit38 ? 1 : 0);
    variable_item_set_current_value_text(item, toggle_text[app->assist_tlssc_bit38 ? 1 : 0]);

    item = variable_item_list_add(list, "MCP Crystal", 3, clock_changed, app);
    variable_item_set_current_value_index(item, app->mcp_clock);
    variable_item_set_current_value_text(item, clock_text[app->mcp_clock]);

    view_dispatcher_switch_to_view(app->view_dispatcher, TeslaFSDViewVarItemList);
}

bool tesla_fsd_scene_settings_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void tesla_fsd_scene_settings_on_exit(void* context) {
    TeslaFSDApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
