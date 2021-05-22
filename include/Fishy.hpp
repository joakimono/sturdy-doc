#pragma once
/** \file */

/**
   Ocean creatures
*/
namespace ocean {

  /**
     Generic creature.
     1. *italic*
     2. **bold**
  */
  struct creature
  {

  };


  /**
* Fishy business
*
* \rststar
*
* +-------------------+-------------------+
* | Grid Tables       | Are Beautiful     |
* +===================+===================+
* | Easy to read      | In code and docs  |
* +-------------------+-------------------+
*
* .. note::
*
*     what
*
* \endrststar

  */
  class fish : protected creature
  {
  public:
    /**
       Do something to the fish
    */
    void fish_me();

    fish() = default;
  };

  /**
     Fish types
  */
  enum class fish_type : int
  {
    mackerel=-1, salmon=0, halibut=1
  };

}
