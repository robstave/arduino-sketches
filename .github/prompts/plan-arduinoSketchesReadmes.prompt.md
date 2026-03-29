# Plan: Multi-Folder README + Annotation Suite

Create readmes and annotations across 6 top-level areas. The theme throughout is **high school learners exploring cause-and-effect by tweaking code** — not understanding every line of math.

---

## Tasks

### 1. Starfield parent folder
Create `ledmatrix/starfield/readme.md` as a "baseline" explaining the 3-sketch progression:
- starfield1 → creates the star field
- starfield2 → adds joystick steering
- starfield3 → adds laser fire

Keep the 3D math as a fun "it just works" black box with nudges to tweak `speed`, `NUM_STARS`, field-of-view divisor (`1.5`), etc. The goal is exploration through cause-and-effect, not understanding the projection math.

---

### 2. starfield3 readme
Create `ledmatrix/starfield/starfield3/readme.md` explaining:
- How laser fire works: button press spawns two `Laser` structs from "wing cannons" (left at x=-3, right at x=+3)
- Lasers travel away from you (z increases) at 3× star speed
- Joystick steers both stars and lasers together
- Key tweak targets: `MAX_LASERS`, laser speed multiplier (`speed * 3.0`), cannon x/y offsets, `lastButtonState` debounce

---

### 3. visual1 readme
Create `ledmatrix/visual1/README.md`. Frame it as an AI experiment:
- Goal was a Matrix-style digital rain effect with a "fade trail"
- The LED matrix does **not** support PWM — `renderBitmap()` writes the whole panel at once, so the refresh cycle is too slow for persistence-of-vision dimming. Pixels that are supposed to "dim" just blink on and off instead.
- Workaround used: a `bright[row][col]` counter per pixel. Head sets it to `MAX_BRIGHT`, then it counts down by 1 each tick. Pixel is ON while > 0. This simulates a fade trail by pixels winking out one-by-one.
- Joystick: A0 = wind (lean rain columns left/right), A2 button = freeze/unfreeze rain
- Explain this is a great starting point for AI-assisted tinkering — describe what you want, run it, see what breaks, iterate.

---

### 4. ledmatrix parent readme
Create `ledmatrix/README.md` with:
- One-line intro: "Sketches featuring the built-in LED matrix on the Arduino UNO R4 WiFi"
- **Project table** (columns: Sketch | Readme | Requirements)

| Sketch | Readme | Requirements |
|--------|--------|--------------|
| alphanum | [alphanum/README.md](alphanum/README.md) | None |
| bytebeat | bytebeat/README.md (stub) | None |
| car-driving | [car-driving/README.md](car-driving/README.md) | None |
| eyeball/eye1 | [eyeball/eye1/readme.md](eyeball/eye1/readme.md) | Joystick |
| starfield1 | [starfield/starfield1/readme.md](starfield/starfield1/readme.md) | None |
| starfield2 | [starfield/starfield2/readme.md](starfield/starfield2/readme.md) | Joystick |
| starfield3 | [starfield/starfield3/readme.md](starfield/starfield3/readme.md) | Joystick |
| visual1 | [visual1/README.md](visual1/README.md) | Joystick |

- **BOM section** (stub for user to fill in): resistors, wiring notes, etc.
- Create stub `bytebeat/README.md` since no readme exists there.

**Open question:** starfield1 and starfield2 already have math-heavy readmes with LaTeX equations. Simplify to match high-school tone, or leave as-is?

---

### 5. ldr readme
Create `ldr/README.md` introducing:
- The **Flying Fish LDR breakout board**
  - [Instructables User Manual](https://www.instructables.com/LDR-Sensor-Module-Users-Manual-V10/)
  - [Hackster.io guide](https://www.hackster.io/ingo-lohs/light-sensing-with-the-flying-fish-series-from-mh-0e51ab)
- Wiring: analog out → A5, digital threshold out → A4, output LED → pin 13
- The three sub-sketches as a progression:
  - `flyingfish1` — reads analog + digital, writes PWM to pin 13
  - `flyingfish1-1` — debug-focused: Serial Monitor output is the main point; learning to read sensor values and understand what the board is seeing. **Consider renaming to `flyingfish-debug`.**
  - `flyingfishled` — adds the Arduino UNO R4 built-in LED matrix as a live bar chart display
- Emphasize **Serial Monitor debugging** as the core learning skill: open the monitor, watch the numbers change as you cover/uncover the sensor

**Open question:** Rename `flyingfish1-1` folder/file to `flyingfish-debug` now, or just note the suggestion?

---

### 6. servos readmes
Create:
- `servos/README.md` — intro to servo control, what a PWM servo signal is (briefly), pin 9 / pin 10
- `servos/one_servo/README.md` — single servo sweeping 0→180→0 over 3 seconds. Key tweak targets: `SWEEP_TIME_MS`, `STEP_DELAY`
- `servos/two_servo/README.md` — two servos sweeping in sync on pins 9 and 10. Same constants. Suggest tweaking one to go in opposite direction.

---

### 7. traffic-light readmes
Create:
- `traffic-light/README.md` — intro with:
  - [Amazon traffic light module link](https://www.amazon.com/Traffic-Display-Module-Arduino-Mini-Traffic/dp/B07SZMRSDN/)
  - Note that plain LEDs + resistors work equally well (pins 11/12/13 for one intersection, 5/6/7 for second)
  - The 4-sketch progression (flat → functions → two intersections → LED module)
- `traffic-light/traffic-one/README.md` — flat code, everything inline in `loop()`. Good first sketch, easy to read top-to-bottom.
- `traffic-light/traffic_one_function/README.md` — introduces a `setLight1()` function and `enum TrafficLight`. Explains why functions make code cleaner and reusable. Note the bug: `switch` statement has `digitalWrite` calls outside any `case` (they run on every call but before the `switch` actually selects).
- `traffic-light/traffic__two_function/README.md` — two intersections with a shared `setLights(light1, light2)` function and `setAllOff()`. Explains how the intersection timing works (one green while other is red, yellow transition, brief all-red).
- `traffic-light/traffic__two_function_led/README.md` — same logic as above, notes this version is wired for the dedicated LED traffic light module.

---

### 8. Top-level README
Replace stub `README.md` (currently just `# arduino-sketches`) with a proper overview:
- Repo description: a collection of Arduino sketches for learning with the Arduino UNO R4 WiFi
- Target audience: high school students
- Section table with one-line descriptions and links:

| Folder | Description |
|--------|-------------|
| [ldr/](ldr/) | Light sensor experiments using the Flying Fish LDR module |
| [ledmatrix/](ledmatrix/) | Animations and visuals using the UNO R4's built-in LED matrix |
| [servos/](servos/) | Servo motor control — sweep and positioning |
| [traffic-light/](traffic-light/) | Traffic light sequences, from simple to two-intersection timing |

- Brief hardware overview (what an Arduino UNO R4 WiFi is)
- Link to each section's readme

---

## Open Questions / Decisions Needed

1. **starfield1/starfield2 existing readmes** are math-heavy with LaTeX equations — simplify to match high-school tone, or leave as-is?  - leave as-is for now, but consider adding a "For the Curious" section at the end with the math details, so students can choose their own adventure between cause-and-effect exploration vs. deep-diving into the projection math.
2. **flyingfish1-1 rename** — rename folder/file to `flyingfish-debug` now, or just note the suggestion in the readme? rename now to avoid confusion, since the current name doesn't clearly convey the purpose of the sketch.
3. **bytebeat** — no `.ino` file was found; should the stub readme describe it as a placeholder/work-in-progress? I m odified the directory.  Note in arduino projects, the main sketch file must have the same name as the folder. So for `bytebeat`, the sketch file should be `bytebeat.ino`. If it's missing, we can either create a placeholder `bytebeat.ino` with a simple "Hello World" sketch or update the readme to explain that this sketch is a work in progress and will be added soon. I recommend creating a placeholder `bytebeat.ino` to maintain consistency across projects and avoid confusion for users browsing the repo.
