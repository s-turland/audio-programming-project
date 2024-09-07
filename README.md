# audio programming project

## references

[demo video on YouTube](https://www.youtube.com/watch?v=m27jSpFIRqA)

### Features of [Rings resonator](https://pichenettes.github.io/mutable-instruments-documentation/modules/rings/) (Three resonator models)
1. **Modal resonator** (features are below)
2. **Sympathetic strings**, modelled by a network of comb filters.
3. **String with non-linearity/dispersion** (comb filter with multimode filter and non-linearities in the loop).

#### [Modal resonator](https://pichenettes.github.io/mutable-instruments-documentation/modules/elements/#modal-resonator)
- Internally uses 64 zero-delay feedback state variable filters.
- **Coarse**, fine and FM frequency controls.
- **Geometry**: Interpolates through a collection of structures, including plates, strings, tubes, bowls.
- **Brightness**. Specifies the character of the material the resonating structure is made of – from wood to glass, from nylon to steel.
- **Damping**. Adds damping to the sound – simulates a wet material or the muting of the vibrations.
- **Position**. Specifies at which point the structure is excited.
- **Space**. Creates an increasingly rich stereo output by capturing the sound at two different points of the structure, and then adds more space through algorithmic reverberation.