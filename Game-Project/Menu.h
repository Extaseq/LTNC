#ifndef _MENU_H
#define _MENU_H

#include "AssetManager.h"
#include "Button.h"

class Menu
{
private:

    AssetManager* mAssetMgr;

    Graphics* mGraphics;

    std::string bg_name = "";

    std::vector<Button*> mButtons;

public:

    Menu(const std::string& name) : bg_name(name)
    {
        mAssetMgr = AssetManager::Instance();

        mGraphics = Graphics::Instance();
    }

    void AddButton(Button* button)
    {
        mButtons.push_back(button);
    }

    std::string GetButtonClicked()
    {
        for (Button* button : mButtons)
        {
            if (button->OnMouseHover())
            {
                return button->GetName();
            }
        }
        return "NULL";
    }

    void Update()
    {
        for (Button* button : mButtons) button->Update();
    }

    void Draw()
    {
        mGraphics->DrawTexture(mAssetMgr->GetTexture(bg_name), NULL, NULL);

        for (Button* button : mButtons) button->Draw();
    }
};

#endif // _MENU_H
