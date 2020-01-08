<?php
/**
 * @file
 * Template to display a @module directory.
 * @Autor Juan Ceballos
 * 
 * @see template directory Full Results.
 */
	if (isset($node->field_directorio_unidad)) {
	    $unidad = $wrapper->field_directorio_unidad->value();
	 	$list 	= reset($unidad->field_dependencias['und']);
	    $data   = $list['tabledata']['tabledata'];
	}elseif ($node->field_directorio) {
		    $unidad = $wrapper->field_directorio->value();
    		$data   = $unidad['tabledata']['tabledata'];
	}

?>

<?php foreach ($data as $key => $value): $remove_data_empty = array_filter($value); ?>
	
	<?php if ($key == 'row_0'): ?>
		<?php foreach ($value as $count => $info): ?>
			<?php !empty($info) ? $header[$count] = $info : print(''); ?>
			<?php endforeach; ?>
	<?php endif; ?>	


	<?php if ($key != 'row_0' && !empty($remove_data_empty)): ?>
		<div class="directory <?php print($key); ?> ">
			<?php for($i=0; $i<=count($header); $i++): ?>
				<?php if(!empty($value['col_'.$i])): ?>
					<div class="info-place_<?php print($i); ?>">
						<p class="label-name-col"><?php print($header['col_'.$i]) ?> </p>
						<p class="data-name-col">
							<?php print($value['col_'.$i]); ?> 
						</p>
					</div>
			<?php endif; ?>
			<?php endfor; ?>
		</div>

	<?php  endif; ?>	

<?php endforeach; ?>