// This is the source code of AyuGram for Desktop.
//
// We do not and cannot prevent the use of our code,
// but be respectful and credit the original author.
//
// Copyright @Radolyn, 2026
#pragma once

namespace AyuUiSettings {

inline constexpr int kMaxAvatarCorners = 23;

void setMonoFont(QString newFont);
QString getMonoFont();

void setWideMultiplier(double val);

bool isWideMultiplied();
int getWideMultiplied(int width, double mult);

void setMaterialSwitches(bool val);
bool isMaterialSwitches();

void setMaterialMenus(bool val);
bool isMaterialMenus();
void setMaterialSettings(bool val);
bool isMaterialSettings();
void setMaterialDialogs(bool val);
bool isMaterialDialogs();
int menuRadius(int radius);
int settingsRowExtra();
int dialogRadius(int radius);

void setAvatarCorners(int val);
int getAvatarCorners();

}
