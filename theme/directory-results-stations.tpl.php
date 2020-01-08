<?php
/**
 * @file
 * Template to display a @module directory.
 * @Autor Juan Ceballos
 * 
 * @see template directory statuions Results.
 */
	$unidad = $wrapper->field_directorio_unidad->value();
 	$list 	= reset($unidad->field_estaciones_cais['und']);
    $data   = $list['tabledata']['tabledata'];
	$headers = $data['row_0'];
	unset($data['row_0']);
	$directory = FALSE;    
?>
<?php foreach ($data as $row):?>
	<?php 
		$row = array_values($row);
		$headers = array_values($headers);
	?>
	<?php if (!empty($row[array_search('Estación',$headers)])):?>	
		<div class="directory <?php print('row_'.($directory+TRUE)); ?>">
		<?php foreach ($row as $keyCol => $valueCol):?>

			<?php if (!empty($valueCol)):?>			
				<div class="info-place_<?php print($keyCol); ?>">
					<p class="label-name-col"><?php print($headers[$keyCol]); ?> </p>
					<p class="data-name-col">
						<?php print($valueCol); ?> 
					</p>
				</div>
				<?php 
				 if (strtolower($headers[$keyCol]) == 'lat') {
					$lat = $valueCol;
				 }
				 if (strtolower($headers[$keyCol]) == 'long') {
					$long = $valueCol;
				 }
				?>
			<?php endif;?>					
		<?php endforeach;?>
		<?php $dataloc = $lat.",".$long;?>
			<iframe src="https://maps.google.com/maps/embed/v1/place?q=<?php echo $dataloc;?>&key=<?php echo variable_get('apykey', '');?>" width="360" height="270" frameborder="0" style="border:0">
			</iframe>	
		</div>
	<?php $directory++;?>
	<?php endif;?>
<?php endforeach;?>