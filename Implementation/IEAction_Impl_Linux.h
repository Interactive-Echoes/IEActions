// SPDX-License-Identifier: GPL-2.0-only
// Copyright © Interactive Echoes. All rights reserved.
// Author: mozahzah

#pragma once

#include "IEActions.h"

#if defined (__linux__)
#include "IEAudio4Linux.h"

class IEAction_Volume_Impl_Linux : public IEAction_Volume
{
public:
    IEAction_Volume_Impl_Linux();
    ~IEAction_Volume_Impl_Linux();

public:
    float GetVolume() const override;
    void SetVolume(float Volume) override;

private:
    static void MixerEventCallback(void* UserData);

private:
    IEMixerElement& m_IEMixerElement;
    const uint32_t m_MixerEventCallbackID;
};

class IEAction_Mute_Impl_Linux : public IEAction_Mute
{
public:
    IEAction_Mute_Impl_Linux();
    ~IEAction_Mute_Impl_Linux();

public:
    bool GetMute() const override;
    void SetMute(bool bMute) override;

private:
    static void MixerEventCallback(void* UserData);

private:
    IEMixerElement& m_IEMixerElement;
    uint32_t m_MixerEventCallbackID = 0;
};

class IEAction_ConsoleCommand_Impl_Linux : public IEAction_ConsoleCommand
{
public:
    void ExecuteConsoleCommand(const std::string& ConsoleCommand, float CommandParameterValue = 0.0f) override;
};

class IEAction_OpenFile_Impl_Linux : public IEAction_OpenFile
{
public:
    void OpenFile(const std::string& FilePath) override;
};
#endif