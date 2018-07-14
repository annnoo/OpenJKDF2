#include "user32.h"

#include "uc_utils.h"
#include "main.h"

uint32_t User32::LoadIconA(uint32_t a, uint32_t b)
{
    return 0;
}

uint32_t User32::LoadCursorA(uint32_t a, uint32_t b)
{
    return 0;
}

uint32_t User32::RegisterClassExA(struct WNDCLASSEXA* lpwcx)
{
    char *menuName = (char*)uc_ptr_to_real_ptr(lpwcx->lpszMenuName);
    char* className = (char*)uc_ptr_to_real_ptr(lpwcx->lpszClassName);
    
    lpfnWndProc = lpwcx->lpfnWndProc;
    
    printf("Register class %s, %s\n", menuName, className);
    return 444;
}

uint32_t User32::FindWindowA(uint32_t a, uint32_t b)
{
    return 0;
}

uint32_t User32::GetSystemMetrics(uint32_t metric)
{        
    switch (metric)
    {
        case 0: //hres
            return 1280;
        case 1: //vres
            return 1024;
        case 15:
        case 32:
            return 0;
        default:
            printf("Unknown metric %x\n", metric);
            return 16;
    }
}

uint32_t User32::CreateWindowExA(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f, uint32_t g, uint32_t h, uint32_t i, uint32_t j, uint32_t k, uint32_t l)
{
    uint32_t hWnd = hWndCnt++;
    
    activeWindow = hWnd;
    SendMessage(hWnd, WM_CREATE);
    return hWnd;
}

uint32_t User32::ShowWindow(uint32_t hWnd, uint32_t show)
{
    SendMessage(hWnd, WM_ACTIVATE, WA_ACTIVE);
    SendMessage(hWnd, WM_ACTIVATEAPP, 1);
    return 0;
}

uint32_t User32::UpdateWindow(uint32_t hWnd)
{
    SendMessage(hWnd, WM_PAINT);
    return 1;
}

uint32_t User32::GetActiveWindow()
{
    return activeWindow;
}

uint32_t User32::GetLastActivePopup(uint32_t hWnd)
{
    return 123;
}

void User32::MessageBoxA(uint32_t hWnd, uint32_t lpText, uint32_t lpCaption, uint32_t uType)
{
    std::string text = vm_read_string(lpText);
    std::string caption = vm_read_string(lpCaption);
    
    printf("MessageBoxA: [%s] %s\n", caption.c_str(), text.c_str());
}

void User32::MessageBoxW(uint32_t hWnd, uint32_t lpText, uint32_t lpCaption, uint32_t uType)
{
    std::string text = vm_read_wstring(lpText);
    std::string caption = vm_read_wstring(lpCaption);
    
    printf("MessageBoxW: [%s] %s\n", caption.c_str(), text.c_str());
}

uint32_t User32::GetDC(uint32_t a)
{
    return 0xefab;
}
  
uint32_t User32::ReleaseDC(uint32_t a, uint32_t b)
{
    return 1;
}
    
uint32_t User32::EnumDisplaySettingsA(uint32_t a, uint32_t b, uint32_t c)
{
    return 1;
}
    
uint32_t User32::ChangeDisplaySettingsA(uint32_t a, uint32_t b)
{
    return 1;
}

uint32_t User32::SetWindowPos(uint32_t hWnd, uint32_t hWndInsertAfter, uint32_t x, uint32_t y, uint32_t cx, uint32_t cy, uint32_t uFlags)    
{
    //SendMessage(hWnd, WM_WINDOWPOSCHANGING);

    return 1;
}

uint32_t User32::GetDesktopWindow()    
{
    return 0xabcd;
}

uint32_t User32::ShowCursor(bool show)
{
    static int count;
    
    return show ? ++count : --count;
}


/*
void handleKeyDown()
{
    if(CURRENT_ITEM_DRAGGED != -1) return;

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    const Uint32 modstate = SDL_GetModState();

    //continuous-response keys
    if (keystate[SDL_SCANCODE_UP])
    {
        button_move_up();
    }
    else if (keystate[SDL_SCANCODE_RIGHT])
    {
        button_move_right();
    }
    else if (keystate[SDL_SCANCODE_LEFT])
    {
        button_move_left();
    }
    else if (keystate[SDL_SCANCODE_DOWN])
    {
        button_move_down();
    }

    if (modstate & (KMOD_LSHIFT | KMOD_RSHIFT))
    {
        button_push();
    }

    if (keystate[SDL_SCANCODE_SPACE])
    {
        button_fire();
    }
}

void handleTouchEvent(SDL_TouchFingerEvent* event)
{
    if (event->type == SDL_FINGERUP)
        ui_touch_up();
    else if (event->type == SDL_FINGERDOWN)
        ui_touch_down();
    else
    {
        ui_set_mouse_abs((int)(event->x*SDL_WIDTH), (int)(event->y*SDL_HEIGHT));
    }
}*/

void handleMouseMove(SDL_MouseMotionEvent *event)
{
    uint32_t pos = ((event->x) & 0xFFFF) | ((event->y << 16) & 0xFFFF0000);

    //user32->SendMessage(user32->GetActiveWindow(), WM_MOUSEMOVE, 0/*TODO*/, pos);
}

void update_input()
{
    uint16_t left, right;
    uint32_t pos, msgl, msgr;
    SDL_MouseButtonEvent* mevent;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                //handleKeyPress(&event.key.keysym);
                break;
            case SDL_MOUSEMOTION:
                handleMouseMove(&event.motion);
                //user32->SendMessage(user32->GetActiveWindow(), WM_PAINT);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                mevent = (SDL_MouseButtonEvent*)&event;
                left = (mevent->button & SDL_BUTTON(SDL_BUTTON_LEFT)) ? 1 : 0;
                right = (mevent->button & SDL_BUTTON(SDL_BUTTON_RIGHT)) ? 2 : 0;
                pos = ((mevent->x) & 0xFFFF) | ((mevent->y << 16) & 0xFFFF0000);
                msgl = event.type == SDL_MOUSEBUTTONDOWN ? WM_LBUTTONDOWN : WM_LBUTTONUP;
                msgr = event.type == SDL_MOUSEBUTTONDOWN ? WM_RBUTTONDOWN : WM_RBUTTONUP;
                
                printf("mouse button %x %x\n", left, right);
                
                if (left)
                    user32->SendMessage(user32->GetActiveWindow(), msgl, left | right, pos);
                if (right)
                    user32->SendMessage(user32->GetActiveWindow(), msgr, left | right, pos);
                user32->SendMessage(user32->GetActiveWindow(), WM_PAINT);
                break;
            /*case SDL_FINGERMOTION:
            case SDL_FINGERDOWN:
            case SDL_FINGERUP:
                //handleTouchEvent((SDL_TouchFingerEvent*)&event);
                break;*/
            case SDL_QUIT:
                printf("Quit!\n");
                //done = TRUE;
                break;
            default:
                break;
        }
    }
    /*handleKeyDown();

    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        mouse_left();

    if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
        mouse_right();*/
}

uint32_t User32::PeekMessageA(struct tagMSG* lpMsg, uint32_t hWnd, uint16_t wMsgFilterMin, uint16_t wMsgFilterMax, uint16_t wRemoveMsg)
{
    //SDL_UpdateWindowSurface(displayWindow);
    //SDL_RenderPresent(displayRenderer);
    update_input();

    if (messages.size())
    {
        *lpMsg = messages.front();
        if (wRemoveMsg)
            messages.pop();
        return 1;
    }

    return 0;
}

uint32_t User32::GetMessageA(struct tagMSG* lpMsg, uint32_t hWnd, uint16_t wMsgFilterMin, uint16_t wMsgFilterMax)
{
    if (messages.size())
    {
        *lpMsg = messages.front();
        messages.pop();
        return 1;
    }

    return 0;
}

uint32_t User32::TranslateMessage(struct tagMSG* lpMsg)
{
    
    return 1;
}

uint32_t User32::DispatchMessageA(struct tagMSG* lpMsg)
{
    uint32_t callback_args[4] = {lpMsg->hWnd, lpMsg->message, lpMsg->wParam, lpMsg->lParam};
    vm_call_function(lpfnWndProc, 4, callback_args, false);
    
    return 1;
}

uint32_t User32::DefWindowProcA(uint32_t hWnd, uint32_t msg, uint32_t wParam, uint32_t lParam)
{
    printf("STUB: DefWindowProcA(0x%04x, 0x%08x, 0x%04x, 0x%08x)\n", hWnd, msg, wParam, lParam);
    return 1;
}

uint32_t User32::SetFocus(uint32_t hWnd)
{
    return hWnd;
}


/*uint32_t User32::(uint32_t )
{
}*/