#!/usr/bin/wish

################################################################################
# This program sets up a game of checkers for two players.                     #
################################################################################

# Set some global variables.

set m 8   ;# number of checkerboard rows
set n 8   ;# number of checkerboard columns

set dames1 12   ;# initial number of dames of player 1
set dames2 12   ;# initial number of dames of player 2
set queens1 0   ;# initial number of queens of player 1
set queens2 0   ;# initial number of queens of player 2

# Define some colors.

set frame_color1   "#8a4524"   ;# "sienna4"
set frame_color2   "#dfba86"   ;# "burlywood"
set board_color1   "#ffffff"   ;# "white"
set board_color2   "#000000"   ;# "black"
set board_color3   "#656565"   ;# "gray40"
set dame_color1    "#0000ce"   ;# "blue3"
set dame_color2    "#ce0000"   ;# "red3"
set queen_color1   "#00beff"   ;# "deepskyblue"
set queen_color2   "#ff4500"   ;# "orangered1"

# Negotiate with the window manager.

wm title . "Tk Checkers"
wm iconname . "Tk Checkers"
wm resizable . 0 0

#------------------------------------------------------------------------------#
# This procedure creates some images.                                          #
#------------------------------------------------------------------------------#

proc create_images {} {
   global dame_color1 dame_color2 queen_color1 queen_color2
   set data {
      #define mask_width 18
      #define mask_height 18
      static unsigned char mask_bits[] = {
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   }
   image create bitmap blank -data $data -maskdata $data
   set data {
      #define circle_width 18
      #define circle_height 18
      static unsigned char circle_bits[] = {
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0xe0, 0x1f, 0x00,
         0xf0, 0x3f, 0x00, 0xf8, 0x7f, 0x00, 0xf8, 0x7f, 0x00, 0xfc, 0xff, 0x00,
         0xfc, 0xff, 0x00, 0xfc, 0xff, 0x00, 0xfc, 0xff, 0x00, 0xf8, 0x7f, 0x00,
         0xf8, 0x7f, 0x00, 0xf0, 0x3f, 0x00, 0xe0, 0x1f, 0x00, 0x80, 0x07, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
   }
   image create bitmap dame1  -foreground $dame_color1  -background {} \
                              -data $data
   image create bitmap dame2  -foreground $dame_color2  -background {} \
                              -data $data
   image create bitmap queen1 -foreground $queen_color1 -background {} \
                              -data $data
   image create bitmap queen2 -foreground $queen_color2 -background {} \
                              -data $data
}

#------------------------------------------------------------------------------#
# This procedure creates and assembles the various widgets.                    #
#------------------------------------------------------------------------------#

proc initialize_game {} {
   global m n
   global frame_color1 frame_color2
   global board_color1 board_color2 board_color3
   global dames1 dames2 queens1 queens2 dame_color1 dame_color2
   frame .f        -background $board_color2 -borderwidth 2 -relief ridge
   frame .f1       -background $frame_color1 -borderwidth 1 -relief raised
   frame .f1.f2    -background $frame_color2 -borderwidth 2 -relief groove
   frame .f1.f2.f3 -background $frame_color2 -borderwidth 4 -relief groove
   pack .f
   pack .f1       -in .f
   pack .f1.f2    -padx 13 -pady 13
   pack .f1.f2.f3 -padx 10 -pady 10
   create_images
   for {set i 1} {$i <= $m} {incr i} {
      for {set j 1} {$j <= $n} {incr j} {
         switch [expr ($i + $j) % 2] {
            0 {
               set background $board_color1
               set activebackground $board_color1
            } 1 {
               set background $board_color2
               set activebackground $board_color3
            }
         }
         button .b($i,$j) -background $background \
                          -activebackground $activebackground \
                          -borderwidth 0 -highlightthickness 0 \
                          -relief flat -anchor nw \
                          -image blank -command "respond_to_click $i $j"
         grid .b($i,$j) -in .f1.f2.f3 -row $i -column $j
      }
   }

   frame .bar1 -background $frame_color1 -relief raised -borderwidth 1
   frame .bar2 -background $frame_color1 -relief raised -borderwidth 1
   label .p1      -background $frame_color1 -foreground $dame_color1 \
                  -text "player 1: "
   label .d1      -background $frame_color1 -foreground $dame_color1 \
                  -text "dames:"
   label .dames1  -background $frame_color1 -foreground $dame_color1 \
                  -textvariable dames1 -width 2
   label .q1      -background $frame_color1 -foreground $dame_color1 \
                  -text "queens:"
   label .queens1 -background $frame_color1 -foreground $dame_color1 \
                  -textvariable queens1 -width 2
   label .p2      -background $frame_color1 -foreground $dame_color2 \
                  -text "player 2: "
   label .d2      -background $frame_color1 -foreground $dame_color2 \
                  -text "dames:"
   label .dames2  -background $frame_color1 -foreground $dame_color2 \
                  -textvariable dames2 -width 2
   label .q2      -background $frame_color1 -foreground $dame_color2 \
                  -text "queens:"
   label .queens2 -background $frame_color1 -foreground $dame_color2 \
                  -textvariable queens2 -width 2
   pack .bar1 -in .f -before .f1 -ipady 1m -fill x
   pack .bar2 -in .f -after  .f1 -ipady 1m -fill x
   pack .p1 .d1 .dames1 .q1 .queens1 -in .bar1 -side left -expand 1 -fill x
   pack .p2 .d2 .dames2 .q2 .queens2 -in .bar2 -side left -expand 1 -fill x

   frame .score1
   frame .score2
   button .draw1    -background "#000" -foreground "#fff" \
                    -activebackground "gray40" -activeforeground "#000" \
                    -highlightthickness 0 -borderwidth 2 \
                    -relief sunken -text "The game is draw." \
                    -command reset_game
   button .draw2    -background "#000" -foreground "#fff" \
                    -activebackground "gray40" -activeforeground "#000" \
                    -highlightthickness 0 -borderwidth 2 \
                    -relief sunken -text "The game is draw." \
                    -command reset_game
   button .onewins1 -background "#000" -foreground "#fff" \
                    -activebackground "gray40" -activeforeground "#000" \
                    -highlightthickness 0 -borderwidth 2 \
                    -relief sunken -text "Player 1 Wins!" \
                    -command reset_game
   button .onewins2 -background "#000" -foreground "#fff" \
                    -activebackground "gray40" -activeforeground "#000" \
                    -highlightthickness 0 -borderwidth 2 \
                    -relief sunken -text "Player 1 Wins!" \
                    -command reset_game
   button .twowins1 -background "#000" -foreground "#fff" \
                    -activebackground "gray40" -activeforeground "#000" \
                    -highlightthickness 0 -borderwidth 2 \
                    -relief sunken -text "Player 2 Wins!" \
                    -command reset_game
   button .twowins2 -background "#000" -foreground "#fff" \
                    -activebackground "gray40" -activeforeground "#000" \
                    -highlightthickness 0 -borderwidth 2 \
                    -relief sunken -text "Player 2 Wins!" \
                    -command reset_game

   reset_game
}

#------------------------------------------------------------------------------#
# This procedure resets the checkerboard pieces for a new game to take place.  #
#------------------------------------------------------------------------------#

proc reset_game {} {
   global m n
   global dames1 dames2 queens1 queens2
   for {set i 1} {$i <= $m} {incr i} {
      for {set j 1} {$j <= $n} {incr j} {
         if {[expr ($i + $j) % 2] == 1} {
            if {$i <= 3} {
               .b($i,$j) configure -image dame1
            } elseif {$i >= [expr $m - 2]} {
               .b($i,$j) configure -image dame2
            } else {
               .b($i,$j) configure -image blank
            }
         } else {
            .b($i,$j) configure -image blank
         }
      }
   }
   set dames1 12; set dames2 12
   set queens1 0; set queens2 0
   pack forget .score1 .score2 .draw1 .draw2 \
               .onewins1 .onewins2 .twowins1 .twowins2
}

#------------------------------------------------------------------------------#
# This procedure is used to announce the score.
#------------------------------------------------------------------------------#

proc announce_score {winner} {
   pack .score1 -in .f -after  .bar1 -fill x
   pack .score2 -in .f -before .bar2 -fill x
   if {$winner == 1} {
      pack .onewins1 -in .score1 -ipady 1m -fill x
      pack .onewins2 -in .score2 -ipady 1m -fill x
   } elseif {$winner == 2} {
      pack .twowins1 -in .score1 -ipady 1m -fill x
      pack .twowins2 -in .score2 -ipady 1m -fill x
   } else {
      pack .draw1 -in .score1 -ipady 1m -fill x
      pack .draw2 -in .score2 -ipady 1m -fill x
   }
}

#------------------------------------------------------------------------------#
# This procedure controls what happens when a player clicks on a checkerboard  #
# square with the first mouse button.                                          #
#------------------------------------------------------------------------------#

proc respond_to_click {i j} {
   global positions dames1 dames2 queens1 queens2
   if {[llength $positions] == 0} {
      attempt_candidate_selection $i $j
   } elseif {[step_is_legal $i $j]} {
      select_position $i $j
   } elseif {[step_is_final $i $j]} {
      move_piece
      if {[expr $dames1 + $queens1] == 0} {
         announce_score 2
      } elseif {[expr $dames2 + $queens2] == 0} {
         announce_score 1
      }
      if {[determine_player] == 0} {
         announce_score 0
      }
   } else {
      reset_positions
      attempt_candidate_selection $i $j
   }
}

#------------------------------------------------------------------------------#
# This procedure tries to select a candidate for the next move.                #
#------------------------------------------------------------------------------#

proc attempt_candidate_selection {i j} {
   global player
   set content [.b($i,$j) cget -image]
   set candidates "dame$player queen$player"
   if {[lsearch $candidates $content] != -1} {
      select_position $i $j
   }
}

#------------------------------------------------------------------------------#
# This procedure checks whether or not a particular checker step is legal.     #
#------------------------------------------------------------------------------#

proc step_is_legal {i j} {
   global positions player
   if {[string compare [.b($i,$j) cget -image] "blank"] == 0} {
      set x_piece [lindex $positions 0]
      set y_piece [lindex $positions 1]
      set piece [.b($x_piece,$y_piece) cget -image]
      set x_last [lindex $positions [expr [llength $positions] - 2]]
      set y_last [lindex $positions [expr [llength $positions] - 1]]
      if {$i == [expr $x_last + 1]} {
         if {$j == [expr $y_last - 1] || $j == [expr $y_last + 1]} {
            set legal_candidates "dame1 queen1 queen2"
            if {[lsearch $legal_candidates $piece] != -1} {
               if {[llength $positions] == 2} {
                  return 1
               }
            }
         }
      } elseif {$i == [expr $x_last - 1]} {
         if {$j == [expr $y_last - 1] || $j == [expr $y_last + 1]} {
            set legal_candidates "dame2 queen2 queen1"
            if {[lsearch $legal_candidates $piece] != -1} {
               if {[llength $positions] == 2} {
                  return 1
               }
            }
         }  
      } elseif {$i == [expr $x_last + 2]} {
         if {$j == [expr $y_last - 2] || $j == [expr $y_last + 2]} {
            set legal_candidates "dame1 queen1 queen2"
            if {[lsearch $legal_candidates $piece] != -1} {
               set x_middle [expr ($x_last + $i) / 2]
               set y_middle [expr ($y_last + $j) / 2]
               set content [.b($x_middle,$y_middle) cget -image]
               set illegal_content "blank dame$player queen$player"
               if {[lsearch $illegal_content $content] == -1} {
                  return 1
               }
            }
         }
      } elseif {$i == [expr $x_last - 2]} {
         if {$j == [expr $y_last - 2] || $j == [expr $y_last + 2]} {
            set legal_candidates "dame2 queen2 queen1"
            if {[lsearch $legal_candidates $piece] != -1} {
               set x_middle [expr ($x_last + $i) / 2]
               set y_middle [expr ($y_last + $j) / 2]
               set content [.b($x_middle,$y_middle) cget -image]
               set illegal_content "blank dame$player queen$player"
               if {[lsearch $illegal_content $content] == -1} {
                  return 1
               }
            }
         }
      }
   }
   return 0
}

#------------------------------------------------------------------------------#
# This procedure checks whether or not a player wishes to end a move.          #
#------------------------------------------------------------------------------#

proc step_is_final {i j} {
   global positions
   if {[string compare [.b($i,$j) cget -image] "blank"] == 0} {
      set x_last [lindex $positions [expr [llength $positions] - 2]]
      set y_last [lindex $positions [expr [llength $positions] - 1]]
      if {$i == $x_last && $j == $y_last} {
         return 1
      }
   }
   return 0
}

#------------------------------------------------------------------------------#
# This procedure responds to the selection of a legal position.                #
#------------------------------------------------------------------------------#

proc select_position {i j} {
   global positions board_color3
   .b($i,$j) configure -background $board_color3
   lappend positions $i $j
}

#------------------------------------------------------------------------------#
# This procedure performes a checker move.                                     #
#------------------------------------------------------------------------------#

proc move_piece {} {
   global positions m
   global dames1 dames2 queens1 queens2
   set x_initial [lindex $positions 0]
   set y_initial [lindex $positions 1]
   set x_final [lindex $positions [expr [llength $positions] - 2]]
   set y_final [lindex $positions [expr [llength $positions] - 1]]
   set piece [.b($x_initial,$y_initial) cget -image]
   .b($x_initial,$y_initial) configure -image blank
   if {$x_final == 1 && [string compare $piece "dame2"] == 0} {
      incr dames2 -1
      incr queens2 1
      .b($x_final,$y_final) configure -image queen2
   } elseif {$x_final == $m && [string compare $piece "dame1"] == 0} {
      .b($x_final,$y_final) configure -image queen1
      incr dames1 -1
      incr queens1 1
   } else {
      .b($x_final,$y_final) configure -image $piece
   }
   if {[expr ($x_final - $x_initial) % 2] == 0} {
      for {set k 3} {$k <= [expr [llength $positions] - 1]} {incr k 2} {
         set x_i [lindex $positions [expr $k - 3]]
         set y_i [lindex $positions [expr $k - 2]]
         set x_f [lindex $positions [expr $k - 1]]
         set y_f [lindex $positions $k]
         set x_victim [expr ($x_i + $x_f) / 2]
         set y_victim [expr ($y_i + $y_f) / 2]
         set victim [.b($x_victim,$y_victim) cget -image]
         switch $victim {
            "dame1"  {incr dames1 -1}
            "dame2"  {incr dames2 -1}
            "queen1" {incr queens1 -1}
            "queen2" {incr queens2 -1}
         }
         .b($x_victim,$y_victim) configure -image blank
      }
   }
   reset_positions
}

#------------------------------------------------------------------------------#
# This procedure resets the positions selected by a player.                    #
#------------------------------------------------------------------------------#

proc reset_positions {} {
   global positions board_color2
   for {set k 1} {$k <= [llength $positions] - 1} {incr k 2} {
      set i [lindex $positions [expr $k - 1]]
      set j [lindex $positions $k]
      .b($i,$j) configure -background $board_color2
   }
   set positions ""
}

#------------------------------------------------------------------------------#
# This procedure determines whose turn it is.                                  #
#------------------------------------------------------------------------------#

proc determine_player {} {
   global player
   switch $player 1 {set player 2} 2 {set player 1}
   if {[player_can_move]} {
      return 1
   } else {
      set stuck_player $player
      switch $player 1 {set player 2} 2 {set player 1}
      if {[player_can_move]} {
         puts "Player $stuck_player is stuck. Player $player goes again."
         return 1
      } else {
         puts "Both players are stuck."
         return 0
      }
   }
}

#------------------------------------------------------------------------------#
# This procedure checks whether or not a particular player can move.           #
#------------------------------------------------------------------------------#

proc player_can_move {} {
   global player m n
   for {set i 1} {$i <= $m} {incr i} {
      for {set j 1} {$j <= $n} {incr j} {
         set piece [.b($i,$j) cget -image]
         set candidates "dame$player queen$player"
         if {[lsearch $candidates $piece] != -1} {
            if {[piece_can_move $i $j]} {
               return 1
            }
         }
      }
   }
   return 0
}

#------------------------------------------------------------------------------#
# This procedure checks whether or not a particular checker piece can move.    #
#------------------------------------------------------------------------------#

proc piece_can_move {i j} {
   global m n
   set piece [.b($i,$j) cget -image]
   foreach y "[expr $j - 1] [expr $j + 1]" {
      set x [expr $i + 1]
      if {$x <= $m && $y >= 1 && $y <= $n} {
         if {[lsearch "dame1 queen1 queen2" $piece] != -1} {
            set candidate [.b($x,$y) cget -image]
            if {[string compare $candidate "blank"] == 0} {
               return 1
            }
         }
      }
      set x [expr $i - 1]
      if {$x >= 1 && $y >= 1 && $y <= $n} {
         if {[lsearch "dame2 queen2 queen1" $piece] != -1} {
            set candidate [.b($x,$y) cget -image]
            if {[string compare $candidate "blank"] == 0} {
               return 1
            }
         }
      }
   }
   foreach y "[expr $j - 2] [expr $j + 2]" {
      set x [expr $i + 2]
      if {$x <= $m && $y >= 1 && $y <= $n} {
         set candidate [.b($x,$y) cget -image]
         if {[string compare $candidate "blank"] == 0} {
            set x_enemy [expr ($i + $x) / 2]
            set y_enemy [expr ($j + $y) / 2]
            set candidate_enemy [.b($x_enemy,$y_enemy) cget -image]
            if {([lsearch "dame1 queen1" $piece] != -1 &&
                 [lsearch "dame2 queen2" $candidate_enemy] != -1) ||
                ([string compare "queen2" $piece] == 0 &&
                 [lsearch "dame1 queen1" $candidate_enemy] != -1)} {
               return 1
            }
         }
      }
      set x [expr $i - 2]
      if {$x >= 1 && $y >= 1 && $y <= $n} {
         set candidate [.b($x,$y) cget -image]
         if {[string compare $candidate "blank"] == 0} {
            set x_enemy [expr ($i + $x) / 2]
            set y_enemy [expr ($j + $y) / 2]
            set candidate_enemy [.b($x_enemy,$y_enemy) cget -image]
            if {([lsearch "dame2 queen2" $piece] != -1 &&
                 [lsearch "dame1 queen1" $candidate_enemy] != -1) ||
                ([string compare "queen1" $piece] == 0 &&
                 [lsearch "dame2 queen2" $candidate_enemy] != -1)} {
               return 1
            }
         }
      }
   }
   return 0
}

#------------------------------------------------------------------------------#
# Launch the game.                                                             #
#------------------------------------------------------------------------------#

# Launch the game.

set player 2
set positions ""
initialize_game
