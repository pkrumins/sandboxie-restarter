#include <windows.h>
#include <cstdio>

void clickChildButton (HWND dialog, const char *caption) {
    HWND dialogItem = NULL;
    while (1) {
        dialogItem = FindWindowEx(dialog, dialogItem, NULL, NULL);
        if (dialogItem == NULL) {
            break;
        }
        char windowText[255];
        GetWindowText(dialogItem, windowText, 255);
        printf("found subitem: %s\n", windowText);
        if (strcmp(windowText, caption) == 0) {
            SetActiveWindow(dialog);
            SendMessage(dialogItem, BM_CLICK, NULL, NULL);
            break;
        }
    }
}

void clickChildChildButton (HWND dialog, const char *caption) {
    HWND dialogItem = NULL;
    while (1) {
        dialogItem = FindWindowEx(dialog, dialogItem, NULL, NULL);
        if (dialogItem == NULL) {
            break;
        }
        printf("found dialogItem: %x\n", dialogItem);
        clickChildButton(dialogItem, caption);
        clickChildChildButton(dialogItem, caption);
    }
}

int main() {
    while (1) {
        {
            HWND dialog = FindWindow("#32770", "Sandboxie Start");
            if (dialog) {
                printf("Found sandboxie failed to start dialog: %x\n", dialog);
                clickChildButton(dialog, "OK");
            }
        }
        {
            HWND dialog = FindWindow("#32770", "Messages from Sandboxie");
            if (dialog) {
                printf("Found sandboxie dialog: %x\n", dialog);
                clickChildButton(dialog, "&Close");
            }
        }
        {
            HWND dialog = FindWindow("#32770", "Microsoft Windows");
            if (dialog) {
                printf("Found windows close program dialog: %x\n", dialog);
                clickChildChildButton(dialog, "&Close program");
            }
        }

        Sleep(5000);
    }
}
