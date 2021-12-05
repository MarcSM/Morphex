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

#include "../JuceLibraryCode/JuceHeader.h"
#include "processor.h"

#include "gui/panels/morphex_panel.h"

//==============================================================================
/**
*/
class MorphexAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MorphexAudioProcessorEditor (MorphexAudioProcessor&);
    ~MorphexAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MorphexAudioProcessor& m_processor;

    MorphexPanel m_morphexPanel;

    juce::ScopedPointer<juce::ResizableCornerComponent>   m_resizeCorner;
    juce::ScopedPointer<juce::ComponentBoundsConstrainer> m_resizeConstrainer;

    juce::Image m_backgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MorphexAudioProcessorEditor)
};