# Spike: the colour of one pixel

**Question:** do the classes of our domain model fit together to give the colour of one pixel?

**Time limit:** 45 minutes.

**Deliberate exceptions:** no tests, and new files go directly in `src/`. Both are undone
before the branch is merged.

## Scene

- Axes: x right, y up, z forward. The camera looks along z.
- Eye at (0, 0, -1), screen at z = 0, one pixel at (0, 0, 0).
- Ray direction D = pixel - eye = (0, 0, 1).
- Red sphere, centre (0, 0, 9), radius 5.

## Maths

With L = O - C: a = D.D, b = 2 D.L, c = L.L - r², discriminant = b² - 4ac,
t = (-b ± sqrt(discriminant)) / 2a. A hit needs t > 0.

| Centre | L | b | c | Discriminant | t | Pixel |
|---|---|---|---|---|---|---|
| (0, 0, 9) | (0, 0, -10) | -20 | 75 | 100 | 5 or 15 | red |
| (3, 0, 9) | (-3, 0, -10) | -20 | 84 | 64 | 6 or 14 | red |
| (6, 0, 9) | (-6, 0, -10) | -20 | 111 | -44 | none | black |
| (0, 0, -11) | (0, 0, 10) | 20 | 75 | 100 | -5 or -15 | black |

## Manual checks with `make run`

| Centre | Expected | Got |
|---|---|---|
| (0, 0, 9) | red | `(1, 0, 0)` |
| (3, 0, 9) | red | `(1, 0, 0)` |
| (6, 0, 9) | black | `(0, 0, 0)` |
| (0, 0, -11) | black | `(1, 0, 0)` — **bug** |
| (5, 0, 9) | touching | `(1, 0, 0)` |

## Answer: yes, the classes fit

- Colour is its own class, not a Vector: colours mix, clamp and convert to 0-255,
  directions do not.
- [x] **Bug (fixed, tested):** a sphere behind the eye is reported as hit. The discriminant does not change
  when b changes sign, and nothing checks t > 0.
- Touching (discriminant = 0) counts as a hit, because of `>=`. Not decided yet.
- `isHitBy` returns only a bool: it does not say at which t the ray hits.
- The colour decision sits in `main`, where it cannot be tested.
- No tests yet, and the new files are not in their concept folders.
