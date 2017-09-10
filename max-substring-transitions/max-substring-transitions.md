
---
header-includes:
 - \usepackage{amsmath}
 - \usepackage{mathrsfs}
---
[//]: # max-substring-transitions.md
[//]: # Mac Radigan

### Max Substring Transitions

\newcommand{\slfrac}[2]{\left.#1\middle/#2\right.}

$$ \mathbf{S} \in \Gamma, \forall s_k \in \mathbf{S} \mbox{   } f_{0,s_k}  $$

$$ where \mbox{   } f_{n,s_k} = \forall s^{'}_k \in \frac{\partial s_k}{\partial k} s^{'}_k \in \mathbf{S} \to \max \left( n+1, f_{n+1,s^{'}_k} \right) $$
