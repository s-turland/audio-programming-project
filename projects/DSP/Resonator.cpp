#include "Resonator.h"
#include "Oscillator.h"
#include "Resources.h"

namespace DSP {

Resonator::Resonator()
{
}

Resonator::~Resonator()
{
}

void Resonator::prepare(double sampleRate)
{
    // Initialize filters with the sample rate
    for (int i = 0; i < kMaxModes; ++i) {
        filters[i].prepare(sampleRate);
    }

}

void Resonator::process(float* const* output, const float* const* input, unsigned int numChannels, unsigned int numSamples)
{


}

void Resonator::setFrequency(float freqHz)
{
    frequency = freqHz;
}

void Resonator::setStructure(float newStructure)
{
    structure = newStructure;
}

void Resonator::setBrightness(float newBrightness)
{
    brightness = newBrightness;
}

void Resonator::setDamping(float newDamping)
{
    damping = newDamping;
}

void Resonator::setPosition(float newPosition)
{
    position = newPosition;
}

void Resonator::setResolution(int newResolution)
{
    newResolution -= newResolution & 1; // Must be even!
    resolution = std::min(newResolution, kMaxModes);
}

int Resonator::ComputeFilters()
{
    float stiffness = Interpolate(lut_stiffness, structure, 256.0f);
    // linear interpolation to get stiffness
    // const int lut_size = 256;
    // const float m { std::fmax(structure, 0.f) * lut_size }; // structure [0, 1]
    // const float mInt { std::floor(m) };
    // const float mFrac { m - mInt };

    // // Calculate read indices
    // const unsigned int readIndex0 { (lut_size - static_cast<unsigned int>(mInt)) % lut_size };
    // const unsigned int readIndex1 { (readIndex0 + lut_size + 1u) % lut_size };

    // // Read from look up table
    // const float read0 = lut_stiffness[readIndex0];
    // const float read1 = lut_stiffness[readIndex1];

    // //a + (b - a) * index_fractional;
    // float stiffness = read0 + (read1 - read0) * mFrac;
    //

    float harmonic = frequency;
    float stretch_factor = 1.0f;

    float q = 500.0f * Interpolate(lut_4_decades, damping, 256.0f);



    float brightness_attenuation = 1.0f - structure;
    // Reduces the range of brightness when structure is very low, to prevent
    // clipping.
    brightness_attenuation *= brightness_attenuation;
    brightness_attenuation *= brightness_attenuation;
    brightness_attenuation *= brightness_attenuation;

    float brightness = brightness * (1.0f - 0.2f * brightness_attenuation);
    float q_loss = brightness * (2.0f - brightness) * 0.85f + 0.15f;
    float q_loss_damping_rate = structure * (2.0f - structure) * 0.1f;
    int num_modes = 0;
    
    for (int32_t i = 0; i < std::min(kMaxModes, resolution); ++i) 
    {
        float partial_frequency = harmonic * stretch_factor;
        if (partial_frequency >= 0.49f) 
        {
          partial_frequency = 0.49f;
        } 
        else 
        {
          num_modes = i + 1;
        }
        
        // filters[i].(partial_frequency, 1.0f + partial_frequency * q);
        
        
        stretch_factor += stiffness;
        if (stiffness < 0.0f) 
        {
            // Make sure that the partials do not fold back into negative frequencies.
            stiffness *= 0.93f;
        } 
        else 
        {
            // This helps adding a few extra partials in the highest frequencies.
            stiffness *= 0.98f;
        }

        // This prevents the highest partials from decaying too fast.
        q_loss += q_loss_damping_rate * (1.0f - q_loss);
        harmonic += frequency;
        q *= q_loss;
    }
    
    return num_modes;

}   




}