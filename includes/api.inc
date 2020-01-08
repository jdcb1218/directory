<?php 

/**
 * Implements functions().
 */
function getUnidades(){
	
  module_load_include('inc', 'entityform', 'entityform.admin');
  $entityform = entityform_load(variable_get('entity_id_config_poli'), $reset = FALSE);
  $data= reset($entityform->field_cat_dep_city['und']);
	
	$query = new EntityFieldQuery();
	$query->entityCondition('entity_type', 'node')
	  ->entityCondition('bundle', 'unidades')
	  ->propertyCondition('status', 1)
          ->fieldCondition('field_tipo_de_unidad', 'tid', $data['tid'])
	  ->propertyOrderBy('title', 'ASC');
	$result = $query->execute();
	return $result;	
}

function directory_config(){
	module_load_include('inc', 'entityform', 'entityform.admin');
	$entityform = entityform_load(variable_get('entity_id_config_poli'), $reset = FALSE);
	return drupal_get_form($entityform->type . '_entityform_edit_form', $entityform, 'edit', 'page');
}

function getOthertypesUnidad(){
	module_load_include('inc', 'entityform', 'entityform.admin');
	$entityform = entityform_load(variable_get('entity_id_config_poli'), $reset = FALSE);
	foreach ($entityform->field_taxonomy_directory['und'] as $key => $value) {
		$taxonomy_load = taxonomy_term_load($value['target_id']);
		$othertypesunidad[$taxonomy_load->tid] = $taxonomy_load->name;
	}
	foreach ($entityform->field_node_directory['und'] as $key => $value) {
		$node =	node_load($value['target_id']);
		$othertypesunidad[$node->nid] = $node->title;
	}
	return $othertypesunidad;
}


function getListUnidadTax($tid){
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'unidades')
    ->propertyCondition('status', 1)
    ->fieldCondition('field_tipo_de_unidad', 'tid', $tid)
    ->propertyOrderBy('created', 'DESC');
 $result = $query->execute();

 foreach ($result['node'] as $key => $value) {
 	$node =	node_load($value->nid);
  	$othertypesunidad[$node->nid.'-rel-'.$tid] = $node->title;
 }
 return $othertypesunidad; 
}


function search_police_data($data){
 switch ($data['option_search']) {
 	case 'Departamentos y ciudades':
    $output = '';
 	 	$node = node_load($data['search_place']);
 		$wrapper = entity_metadata_wrapper('node', $node);
 		switch ($data['status']) {
 			case '0': // Todos
        $output .= theme('directory-results-dependencies',array('wrapper' => $wrapper,'node' => $node));
 				$output .= theme('directory-results',array('wrapper' => $wrapper,'node' => $node));
 				break;
 			case '1': // Estaciones
 				$output = theme('directory-results-stations',array('wrapper' => $wrapper,'node' => $node));
 				break;
 			case '2': // Cais
 				$output = theme('directory-results-cais',array('wrapper' => $wrapper,'node' => $node));
 				break;
 			case '3': // Cuadrantes
 				$output = theme('directory-results-quadrant',array('wrapper' => $wrapper,'node' => $node));
 				break;
 		}
    break;
    case 'Otros tipos de unidad':
    	$id = $data['other_types_unidad'];
    	foreach ($data as $key => $value) {
    		if (is_numeric($key)) {
    			$args = explode("-", $value);
    			if (in_array($id, $args)){
    				$index = array_shift($args);
    			}
    		}
    	}

      $node = (isset($index)) ? node_load($index) : node_load($id);   
      $wrapper = entity_metadata_wrapper('node', $node);
      $output = theme('directory-results-others-units',array('wrapper' => $wrapper,'node' => $node));
	  break;
    case 'Busqueda personalizada':
        $query = db_select('field_data_field_estaciones_cais', 'f')->fields('f', array(
            'entity_id'
        ))
        ->condition('field_estaciones_cais_value', '%' . db_like($data['keyword_search']) . '%', 'LIKE')
        ->distinct();
        $result = $query->execute();
        $dataSend = array(); 
        foreach ($result as $key => $entityId) {
            if(!array_search($entityId->entity_id, $dataSend)){
                $wrapper = entity_load('unidades',array($entityId->entity_id));
                $wrapper = reset($wrapper);
                $output .= theme('directory-results-keyword',array('wrapper' => $wrapper,'node' => $data['keyword_search']));
                $dataSend[] = $entityId->entity_id;
            }            
        }        
    break; 
 }
 return '<div id="result_places_polices_div">'.$output."</div>"; 
}
