========================================================================
    CONSOLE APPLICATION : Resource File Checker Validators Overview
========================================================================
    Valid   -> creates a tree 
    |       -> manager for all the other validators
    |
    |
    |------ dialog_dimensions   -> checks if the dialog is not out of bounds (checks the height and the width of the dialog)
    |   
    |------ partial_overlapping -> validates the dialog if there are no controllers that overlap partially (no error produced if one controller completely contains another)
    |
    |------ column_alignment    -> finds the controllers which are not left-aligned with other controllers
    |
    |------ standard_dimensions -> for each controller in a dialog, it checks if the controller respects the standard dimensions of its type
    |
    |------ horizontal_alignment-> checks if the middle points of the controllers on the same row are aligned
    |
    |------ padding         	-> checks the distance between two controllers
        	|
        	|
        	|------ padding_vertically  -> checks the vertical distance between all the controllers 
        	|
        	|------ padding_horizontally    -> checks the horizontal distance between all the controllers
        	|
        	|------ padding_type_control    -> checks if there are no padding issues between the elements
		|				   of a list of check boxes or radio buttons
        	|
        	|------ padding groupbox top    -> checks if the uppermost controller of a groupbox respects 
		|				   the padding between itself and the groupbox 
        	|                  		   padding between top of the controller and groupbox
        	|
        	|------ padding groupbox bot    -> checks if the lowermost controller of a groupbox respects 
		|				   the padding between itself and the groupbox
        	|                  		   padding between top of the controller and groupbox
        	|
        	|------ padding groupbox left   -> checks if the  leftmost controller of a groupbox respects 
		|				   the padding between itself and the groupbox
        	|                  		   padding between top of the controller and groupbox
        	|
        	|------ padding groupbox right  -> checks if the rightmost controller of a groupbox respects 
						   the padding between itself and the groupbox
                           			   padding between top of the controller and groupbox


Console arguments:

- dialog_dimensions 	dd
- partial_overlapping 	ol
- column_alignment 	ca
- horizontal_alignment  ha
- standard_dimensions 	sd
- padding 		pd
- dialog margins	dm
- dialog flags		df

/////////////////////////////////////////////////////////////////////////////