/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

#include "Panels/MorphexPanel.h"
//#include "MainPanel.h"
//#include "SMTLookAndFeel.h"

//==============================================================================
/**
*/
class SpectralMorphingToolAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    SpectralMorphingToolAudioProcessorEditor (SpectralMorphingToolAudioProcessor&);
    ~SpectralMorphingToolAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SpectralMorphingToolAudioProcessor& processor;
    
    MorphexPanel morphexPanel;

    ScopedPointer<ResizableCornerComponent> resizeCorner;
    ScopedPointer<ComponentBoundsConstrainer> resizeConstrainer;
    
//    ScopedPointer<MainPanel> mMainPanel;

//    ScopedPointer<SMTLookAndFeel> mLookAndFeel;
    
    Image mBackgroundImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectralMorphingToolAudioProcessorEditor)
};
