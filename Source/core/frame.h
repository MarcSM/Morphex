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

namespace morphex
{
class Frame
{
public:
    Frame();

    struct FftComponent
    {
        std::vector<float> freqs;
        std::vector<float> mags;
        std::vector<float> phases;
    };

    const FftComponent&       getHarmonicComponent() const;
    const FftComponent&       getSinusoidalComponent() const;
    const std::vector<float>& getStochasticWaveform() const;
    const std::vector<float>& getAttackWaveform() const;
    const std::vector<float>& getResidualWaveform() const;
    size_t                    getMaxNumOfHarmonics() const;
    size_t                    getMaxNumOfSinusoids() const;

private:
    FftComponent       harmonic;
    FftComponent       sinusoidal;
    std::vector<float> stochastic;
    std::vector<float> attack;
    std::vector<float> residual;

    bool hasHarmonic() { return harmonic.freqs.size() > 0; };
    bool hasSinusoidal() { return sinusoidal.freqs.size() > 0; };
    bool hasPhases (SoundFrameFMP sound_frame_fmp) { return sound_frame_fmp.phases.size() > 0; };
    bool hasStochastic() { return stochastic.size() > 0; };
    bool hasAttack() { return attack.size() > 0; };
    bool hasResidual() { return residual.size() > 0; };
};
}; // namespace morphex