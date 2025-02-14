// decision_tree.c
#include "decision_tree.h"

// Optimized decision tree for binary classification
int decision_tree(float feature1, float feature2) {
    if (feature1 <= 0.5f) {
        if (feature2 <= 0.5f) {
            return 0; // Class 0
        } else {
            return 1; // Class 1
        }
    } else {
        if (feature2 <= 0.5f) {
            return 1; // Class 1
        } else {
            return 0; // Class 0
        }
    }
}
