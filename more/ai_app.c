// ai_app.c
#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>
#include "decision_tree.h"

// Application state
typedef struct {
    float feature1;
    float feature2;
    int prediction;
} AiApp;

// Draw callback
static void draw_callback(Canvas* canvas, void* ctx) {
    AiApp* app = (AiApp*)ctx;
    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    canvas_draw_str(canvas, 10, 10, "Flipper Zero AI Demo");

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "Feature 1: %.2f", app->feature1);
    canvas_draw_str(canvas, 10, 30, buffer);

    snprintf(buffer, sizeof(buffer), "Feature 2: %.2f", app->feature2);
    canvas_draw_str(canvas, 10, 50, buffer);

    snprintf(buffer, sizeof(buffer), "Prediction: %d", app->prediction);
    canvas_draw_str(canvas, 10, 70, buffer);
}

// Input callback
static void input_callback(InputEvent* input_event, void* ctx) {
    AiApp* app = (AiApp*)ctx;
    if (input_event->type == InputTypePress) {
        if (input_event->key == InputKeyUp) {
            app->feature1 += 0.1f;
        } else if (input_event->key == InputKeyDown) {
            app->feature1 -= 0.1f;
        } else if (input_event->key == InputKeyRight) {
            app->feature2 += 0.1f;
        } else if (input_event->key == InputKeyLeft) {
            app->feature2 -= 0.1f;
        } else if (input_event->key == InputKeyOk) {
            // Make a prediction
            app->prediction = decision_tree(app->feature1, app->feature2);
        }
    }
}

// Main application entry point
int32_t ai_app(void* p) {
    AiApp* app = malloc(sizeof(AiApp));
    app->feature1 = 0.5f;
    app->feature2 = 0.5f;
    app->prediction = -1;

    // Set up view port
    ViewPort* view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, draw_callback, app);
    view_port_input_callback_set(view_port, input_callback, app);

    // Register view port in GUI
    Gui* gui = furi_record_open("gui");
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    // Main loop
    while (1) {
        view_port_update(view_port);
        furi_delay_ms(100);
    }

    // Cleanup
    gui_remove_view_port(gui, view_port);
    view_port_free(view_port);
    free(app);
    furi_record_close("gui");
    return 0;
}
