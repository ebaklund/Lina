
# Venn-diagrams as logic representation
Venn diagrams can be used to represent logic reasoning.
For example, deduction and induction are two classes of logic propositions 
that can be visualized as venn-diagrams.

Fuzzy logic is a known form of logic representation.
We will here use a new terms floating logic to emphasize
a similar logic without the drawback
We hope to show here that logic propositions can be generalized with
floating truth values to express


### Dual (not)
    1 - a
    not [0.0, 0.5, 1.0]
      = [1.0, 0.5, 0.0]

### Intersection (and)
    a*b
        [0.0, 0.5, 1.0, 0.0, 0.5,  1.0, 0.0, 0.5, 1.0]
    and [0.0, 0.0, 0.0, 0.5, 0.5,  0.5, 1.0, 1.0, 1.0] 
      = [0.0, 0.0, 0.0, 0.0, 0.25, 0.5, 0.0, 0.5, 1.0]
    sum([..])/n = 0.25

### Union (or)
    a+b - a*b
       [0.0, 0.5, 1.0, 0.0, 0.5,  1.0, 0.0, 0.5, 1.0]
    or [0.0, 0.0, 0.0, 0.5, 0.5,  0.5, 1.0, 1.0, 1.0] 
     = [0.0, 0.5, 1.0, 0.5, 0.75, 1.0, 1.0, 1.0, 1.0]
    sum([..])/n = 0.75

