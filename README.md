# Efficient reformation demo
This demo project applies the [Hungarian Algorithm](https://github.com/rharel/cpp-hungarian-algorithm) to the problem of reforming units of "vehicles" efficiently in two dimensions. The problem statement:

> Let a vehicle _unit_ be a collection of n > 0 vehicles.
> 
> Let a unit's _formation_ F: [1, n] => R<sup>2</sup> be a mapping between each member of the unit to a position.
>
> A unit is said to _satisfy_ a formation if each member is at its corresponding assigned position.
> 
> Let there be two formations F<sub>1</sub> and F<sub>2</sub>. Given is a unit U satisfying F<sub>1</sub>, and a set of n target positions T. What is the optimal assignment F<sub>2</sub>: [1, n] => T that results in a minimal total traveling distance over all members of U to satisfy F<sub>2</sub>?

# Directory structure

| Directory        | Description               |
| ---------        | -----------               |
| `common/`        | Common dependencies.      |
| `core/`          | Formation description project files.                  |
| `demo/`          | Demo application project files. |
| `documentation/` | [Doxygen](http://www.stack.nl/~dimitri/doxygen/) configuration. |

# License
[MIT](LICENSE.txt)
