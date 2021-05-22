#pragma once
/** \file */

/**
   \brief This is a test class.

   Sharky business

   \rst
   There is a :math:`N^2` environment for reStructuredText!

    +-------------------+-------------------+
    | Grid Tables       | Are Beautiful     |
    +===================+===================+
    | Easy to read      | In code and docs  |
    +-------------------+-------------------+
    | Exceptionally flexible and powerful   |
    +-------+-------+-------+-------+-------+
    | Col 1 | Col 2 | Col 3 | Col 4 | Col 5 |
    +-------+-------+-------+-------+-------+

    \endrst

    \rst
    .. uml::

      ditaa
      +--------+   +-------+    +-------+
      |        | --+ ditaa +--> |       |
      |  Text  |   +-------+    |diagram|
      |Document|   |!magic!|    |       |
      |     {d}|   |       |    |       |
      +---+----+   +-------+    +-------+
      :                         ^
      |       Lots of work      |
      +-------------------------+

    \endrst

*/
struct shark {
  /**
     Do something to the shark

     \f{eqnarray*}{
     g &=& \frac{Gm_2}{r^2} \\
     &=& \frac{(6.673 \times 10^{-11}\,\mbox{m}^3\,\mbox{kg}^{-1}\,
     \mbox{s}^{-2})(5.9736 \times 10^{24}\,\mbox{kg})}{(6371.01\,\mbox{km})^2} \\
     &=& 9.82066032\,\mbox{m/s}^2
     \f}

  */
  void shark_me();

private:
  int teeth; ///< ugly teeth

};
