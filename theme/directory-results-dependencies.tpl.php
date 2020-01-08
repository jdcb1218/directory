<?php
/**
 * @file
 * Template to display a @module directory.
 * @Autor Juan Ceballos
 * 
 * @see template directory Full Results.
 */
	$unidad = $wrapper->field_directorio_unidad->value();
 	$list 	= reset($unidad->field_dependencias['und']);
    $data   = $list['tabledata']['tabledata'];
	$headers = $data['row_0'];
	unset($data['row_0']);
	$directory = FALSE;     
?>
<?php foreach ($data as $row):?>
  <?php  $row = array_filter(array_values($row)); $headers = array_values($headers); ?>
  	<?php if(!empty($row) && !is_numeric(reset($row))): ?>
		<div class="directory <?php print('row_'.($directory+TRUE)); ?>">
			<?php foreach ($row as $keyCol => $valueCol): ?>
				<?php if (!empty($valueCol)): ?>	
					<div class="info-place_<?php print($keyCol); ?>">
						<p class="label-name-col"><?php print($headers[$keyCol]); ?> </p>
						<p class="data-name-col">
							<?php print($valueCol); ?> 
						</p>
					</div>	
				<?php endif;?>					
			<?php endforeach;?>
		</div>
	<?php $directory++;?>
<?php  endif; ?>
<?php endforeach;?>