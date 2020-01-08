<?php 
module_load_include('inc', 'entityform', 'entityform.admin');

/**
 * Implements hook_form().
 */
function directory_form($form, &$form_state) {
    $form = array();
	$result = getUnidades();
	
	foreach ($result['node'] as $key => $value) {
		$node = node_load($value->nid);
		$options[$node->nid] = $node->title;
	}

	$form['directory'] = array(
        '#type' => 'fieldset',
        '#title' => t('Buscar por'),
    );

	$form['directory']['option_search'] = array(
	    '#type' => 'radios',
	    '#options' => drupal_map_assoc(array(
	    				t('Departamentos y ciudades'), 
	    			  	t('Otros tipos de unidad'), 
	    			  	t('Busqueda personalizada'))),
	    '#default_value' => 'Departamentos y ciudades',
	 );
	 
	$unidad = array_pop(explode('/', current_path()));
	
	 $form['directory']['search_place'] = array(
	    '#type' => 'select',
	    '#title' => t('Departamentos y ciudades Information'),
	    '#options' => $options,
	    '#states' => array(
	      'visible' => array(
	        ':input[name="option_search"]' => array('value' => t('Departamentos y ciudades')),
	      ),
	    ),
	    '#default_value' => isset($unidad) ? $unidad : '',
	  );

	$form['directory']['status'] = array(
	   '#type' =>'radios', 
	   '#title' => t('Status'), 
	   '#options' => array(t('Todos'), t('Estaciones'), t('Cais'), t('Cuadrantes')), 
	   '#states' => array(
	      'visible' => array(
	        ':input[name="option_search"]' => array('value' => t('Departamentos y ciudades')),
	      ),
	    ),
	   '#default_value' => 'Todos',
	);


	 $form['directory']['other_types_unidad'] = array(
	    '#type' => 'select',
	    '#options' => getOthertypesUnidad(),
	    '#states' => array(
	      'visible' => array(
	        ':input[name="option_search"]' => array('value' => t('Otros tipos de unidad')),
	      ),
	    ),
	  );

	 $entityform = entityform_load(variable_get('entity_id_config_poli'), $reset = FALSE);
	 foreach ($entityform->field_taxonomy_directory['und'] as $key => $value) {
	 	$form['directory'][$key] = array(
		    '#type' => 'select',
		    '#options' => getListUnidadTax($value['target_id']),
		    '#states' => array(
		      'visible' => array(
		      	':input[name="option_search"]' => array('value' => 'Otros tipos de unidad'),
		        ':input[name="other_types_unidad"]' => array('value' => $value['target_id']),
		      ),
		    ), 
		  ); 	 	
	 }
	 
	$form['directory']['keyword_search'] = array(
	  '#type' => 'textfield', 
	  '#size' => 60, 
	  '#maxlength' => 128, 
	  '#states' => array(
	      'visible' => array(
	        ':input[name="option_search"]' => array('value' => t('Busqueda personalizada')),
	      ),
	   ),	  
	);

  $form['directory']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    '#ajax' => array(
      'callback' => 'directory_form_submit',
      'wrapper' => 'result_places_polices_div',
      'method' => 'replace',
      'effect' => 'fade',
    ), 
  ); 
  
  $form['directory']['result_places_polices'] = array(
    'markup' => l(t('Cancel'), 'foo/bar'),
    '#prefix' => '<div id="result_places_polices_div">',
    '#suffix' => '</div>',
  );

 return $form;
} 

function directory_form_submit($form, $form_state) {
  $info = search_police_data($form_state['values']);
  return $info;
}



/**
 * Implements hook_form().
 */
function directory_config_entity($form, &$form_state) {

  	$form['entity_id_config_poli'] = array(
		'#type' => 'textfield',
		'#attributes' => array('type' => 'number'),
		'#title' => t('Please add Id Entityform'),
		'#required' => true,
		'#maxlength' => 4,
		'#default_value' => variable_get('entity_id_config_poli'),
  	);

	$form['maps'] = array(
	    '#type' => 'fieldset',
	    '#title' => t('Configuration Google Maps'),
	    '#collapsible' => TRUE,
	    '#group' => 'vertical_tabs',
	  );

	  $form['maps']['endpoint'] = array(
	    '#title' => t('End Point'),
	    '#type' => 'textfield',
	    '#description' => t('Example :https://www.google.com/maps/embed/v1/place'),
	    '#default_value' => variable_get('endpoint'),
	  );

	  $form['maps']['apykey'] = array(
	    '#title' => t('Apy Key'),
	    '#type' => 'textfield',
	    '#description' => t('Example :AIzaSyBKH_1vjFYheef6y0VraYVdRJRFbtoRgTE'),
	    '#default_value' => variable_get('apykey'),
	  );

	  $form['maps']['width_windows'] = array(
	    '#title' => t('Width'),
	    '#type' => 'textfield',
	    '#description' => t('Example :500'),
	    '#default_value' => variable_get('width_windows'),
	  );

	  $form['maps']['height_windows'] = array(
	    '#title' => t('Height'),
	    '#type' => 'textfield',
	    '#description' => t('Example :500'),
	    '#default_value' => variable_get('height_windows'),
	  );

	  $form['submit'] = array(
	    '#type' => 'submit',
	    '#value' => t('Submit'),
	  );	
 
	  return $form;
}

/**
 * Implements hook_validate().
 */
function directory_config_entity_validate($form, &$form_state) {
  if (is_numeric($form_state['values']['entity_id_config_poli'])) {
	module_load_include('inc', 'entityform', 'entityform.admin');
	$entityform = entityform_load(trim($form_state['values']['entity_id_config_poli']), $reset = FALSE);
	if($entityform->type != 'config_directory'){
		form_set_error('entity_id_config_poli', t('Please numerical field to config_directory'));
	}
  }else{
  	form_set_error('entity_id_config_poli', t('Please numerical field'));
  }
}

/**
 * Implements hook_submit.
 */
function directory_config_entity_submit($form, &$form_state) {
	foreach ($form_state['values'] as $key => $value) {
		variable_set($key, $value);
	}
	return drupal_set_message(t('Config save'), 'status', TRUE);
}
