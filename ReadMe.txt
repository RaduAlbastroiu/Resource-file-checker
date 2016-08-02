========================================================================
    CONSOLE APPLICATION : Resource File Checker Validators Overview
========================================================================
Validators   

dialog flags 	     -> validates the flags of a dialog

dialog margins		 -> validates the margins of a dialog

dialog_dimensions    -> checks if the dialog is not out of bounds (checks the height and the width of the dialog)

partial_overlapping  -> validates the dialog if there are no controllers that overlap partially (no error produced 
                        if one controller completely contains another)
    
column_alignment     -> finds the controllers which are not left-aligned with other controllers (left alignment)
standard_dimensions  -> for each controller in a dialog, it checks if the controller respects the standard
                        dimensions of its type

horizontal_alignment -> checks if the middle points of the controllers on the same row are aligned

padding         	 -> checks all the things below

	padding_vertically   -> checks the minimum vertical distance between all the controllers 
	
	padding_horizontally -> checks the minimum horizontal distance between all the controllers
	
	padding_first_layer  -> checks the distance between all the controllers of the same type
							on the same column from the first layer and generate issue if the 
							controllers are too separate or too close
	
	padding_type_control -> checks if there are no padding issues between the elements
							of a list of check boxes or radio buttons and checks if the
							distance between controllers of the same list is constant
	
	padding_groupbox     -> checks if the uppermost, leftmost, rightmost, lowermost controller 
							of a groupbox respects the padding between itself and the groupbox 
										
	
Console arguments:

- dialog margins	dm
- dialog flags		df
- dialog_dimensions 	dd
- partial_overlapping 	ol
- column_alignment 	ca
- horizontal_alignment  ha
- standard_dimensions 	sd
- padding 		pd


/////////////////////////////////////////////////////////////////////////////