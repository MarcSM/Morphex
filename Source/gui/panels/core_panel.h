/* Copyright (C) 2020 Marc Sanchez Martinez
 *
 * https://github.com/MarcSM/morphex
 *
 * Morphex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Morphex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Morphex. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <JuceHeader.h>

#include "../components/pad_xy.h"

class CorePanel : public juce::Component
{
public:
    CorePanel (MorphexAudioProcessor& processor) :
        m_instrument (processor.m_synth.m_instrument)
    {
        // Make button toggleable
        m_harmonicButton.setClickingTogglesState (true);
        m_sinusoidalButton.setClickingTogglesState (true);
        m_stochasticButton.setClickingTogglesState (true);
        m_attackButton.setClickingTogglesState (true);
        m_residualButton.setClickingTogglesState (true);

        m_harmonicButton.setToggleState (m_instrument.isModelActive (morphex::Model::Type::Harmonic), juce::NotificationType::dontSendNotification);
        m_sinusoidalButton.setToggleState (m_instrument.isModelActive (morphex::Model::Type::Sinusoidal), juce::NotificationType::dontSendNotification);
        m_stochasticButton.setToggleState (m_instrument.isModelActive (morphex::Model::Type::Stochastic), juce::NotificationType::dontSendNotification);
        m_attackButton.setToggleState (m_instrument.isModelActive (morphex::Model::Type::Attack), juce::NotificationType::dontSendNotification);
        m_residualButton.setToggleState (m_instrument.isModelActive (morphex::Model::Type::Residual), juce::NotificationType::dontSendNotification);

        addAndMakeVisible (m_harmonicButton);
        addAndMakeVisible (m_sinusoidalButton);
        addAndMakeVisible (m_stochasticButton);
        addAndMakeVisible (m_attackButton);
        addAndMakeVisible (m_residualButton);

        // Pad XY
        morphex::Parameter freqs_interp_factor_parameter = morphex::PARAMETERS<float>[morphex::Parameters::FreqsInterpFactor];
        morphex::Parameter mags_interp_factor_parameter  = morphex::PARAMETERS<float>[morphex::Parameters::MagsInterpFactor];

        m_padXy = new PadXY (processor, processor.parameters, freqs_interp_factor_parameter, mags_interp_factor_parameter);

        addAndMakeVisible (m_padXy);
    }

    ~CorePanel()
    {
    }

    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::black);
        //        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        //        getWidth() * 0.75f , getHeight() * 0.75f, true);
        // Background gradient
        juce::ColourGradient cg (GUI::Color::Accent.withAlpha (0.5f),
                                 getWidth() * 0.5f,
                                 getHeight() * 0.5f,
                                 GUI::Color::Accent.withAlpha (0.0f),
                                 getWidth() * 0.65f,
                                 getHeight() * 1.0f,
                                 true);
        g.setFillType (cg);
        g.fillRect (0, 0, getWidth(), getHeight());

        // Core controls
        m_harmonicButton.onClick   = [this] { m_instrument.setActiveModel (morphex::Model::Type::Harmonic, m_harmonicButton.getToggleState()); };
        m_sinusoidalButton.onClick = [this] { m_instrument.setActiveModel (morphex::Model::Type::Sinusoidal, m_sinusoidalButton.getToggleState()); };
        m_stochasticButton.onClick = [this] { m_instrument.setActiveModel (morphex::Model::Type::Stochastic, m_stochasticButton.getToggleState()); };
        m_attackButton.onClick     = [this] { m_instrument.setActiveModel (morphex::Model::Type::Attack, m_attackButton.getToggleState()); };
        m_residualButton.onClick   = [this] { m_instrument.setActiveModel (morphex::Model::Type::Residual, m_residualButton.getToggleState()); };

        // Pad XY

        // Circle glow
        PadXY::PadCircle* circle      = m_padXy->getCircle();
        float             glow_radius = circle->getWidth() * 2.0f;
        float             glow_x      = circle->getX() + (circle->getWidth() / 2.0f) + m_padXy->getX();
        float             glow_y      = circle->getY() + (circle->getHeight() / 2.0f) + m_padXy->getY();
        float             glow_w      = glow_radius * 2.0f;
        float             glow_h      = glow_radius * 2.0f;

        juce::ColourGradient cg_glow (GUI::Color::Accent.withAlpha (0.3f),
                                      glow_x,
                                      glow_y,
                                      GUI::Color::Accent.withAlpha (0.0f),
                                      glow_x + (glow_radius * 0.4f),
                                      glow_y + (glow_radius * 0.4f),
                                      true);

        g.setFillType (cg_glow);
        g.fillRect (0, 0, getWidth(), getHeight());
        //        g.fillRect (glow_x - glow_radius, glow_y - glow_radius, glow_w, glow_h);
    }

    void resized() override
    {
        // Sizes
        const float pad_width  = getWidth();
        const float pad_height = getWidth();

        const float pad_x = 0;
        const float pad_y = 0;
        //        const int pad_y = ( getHeight() - pad_height ) / 2;

        // Pad XY
        m_padXy->setBounds (pad_x, pad_y, pad_width, pad_height);

        const int   num_buttons   = 5;
        const float button_width  = getWidth() / num_buttons;
        const float button_height = (getHeight() - pad_height) / 2;

        // Core controls
        const int core_controls_y = pad_y + pad_height;

        m_harmonicButton.setBounds (0, core_controls_y, button_width, button_height);
        m_sinusoidalButton.setBounds (button_width, core_controls_y, button_width, button_height);
        m_stochasticButton.setBounds (2 * button_width, core_controls_y, button_width, button_height);
        m_attackButton.setBounds (3 * button_width, core_controls_y, button_width, button_height);
        m_residualButton.setBounds (4 * button_width, core_controls_y, button_width, button_height);
    }

    void updateToggleState (juce::Button* button, juce::String name)
    {
        auto         state          = button->getToggleState();
        juce::String stateString    = state ? "ON" : "OFF";
        juce::String selectedString = state ? " (selected)" : "";

        juce::Logger::outputDebugString (name + " Button changed to " + stateString);
        button->setButtonText (name + selectedString);
    }

    template <typename T>
    void updateParameter (T new_value, T& parameter)
    {
        parameter = new_value;
    }

    void updateToggleCoreParameter (juce::Button* button, bool& core_parameter)
    {
        core_parameter = button->getToggleState();
    }

private:
    morphex::Instrument& m_instrument;

    juce::TextButton m_harmonicButton { "Harmonics" };
    juce::TextButton m_sinusoidalButton { "Sinusoidal" };
    juce::TextButton m_stochasticButton { "Stochastic" };
    juce::TextButton m_attackButton { "Attack" };
    juce::TextButton m_residualButton { "Residual" };

    PadXY* m_padXy;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CorePanel)
};