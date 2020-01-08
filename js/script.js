Drupal.behaviors.directory = {
  attach: function (context, settings) {
	jQuery('#edit-option-search-departamentos-y-ciudades').click(function(){
		jQuery("#edit-search-place").removeAttr('disabled');
		jQuery('#edit-search-place').attr('enabled','enabled');
	    jQuery('#edit-other-types-unidad').attr('disabled','disabled');
	    jQuery('#edit-keyword-search').attr('disabled','disabled');
	});

    jQuery('#edit-option-search-otros-tipos-de-unidad').click(function(){
    	jQuery("#edit-other-types-unidad").removeAttr('disabled');
    	jQuery('#edit-other-types-unidad').attr('enabled','enabled');
    	jQuery('#edit-search-place').attr('disabled','disabled');
    	jQuery('#edit-keyword-search').attr('disabled','disabled');
    });

	jQuery('#edit-option-search-busqueda-personalizada').click(function(){
   		jQuery("#edit-keyword-search").removeAttr('disabled');
    	jQuery('#edit-keyword-search').attr('enabled','enabled');	   
	    jQuery('#edit-other-types-unidad').attr('disabled','disabled');
	});
  }
};

jQuery(window).load(function() {
  jQuery('#directory-form .fieldset-wrapper #edit-submit').mousedown();
});