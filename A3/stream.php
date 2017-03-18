<!DOCTYPE html>

<html>
<head>
<?php 
	$username = $_POST["username"];
 ?>
<title><?php echo $stream; ?></title>
</head>

<body>

<h3>Welcome <?php echo $username; ?></h3>
<?php
	$command = "./getStreams ".$username;
	exec($command, $output, $return);
	if (count($output)==0)
		echo "You have not been added to any streams.";
?>

<?php if (count($output) > 0) ?>
<form>
	<?php	
		int $i = 0;
		foreach ($output as $stream) {
		 	echo "<input type=\"radio\" name=\"stream\" value=\"$stream\">"''
		 }
	?>

	<input type="radio" name="stream" value="all">
	<input type="submit" value="View">
</form>
<?php endif ?>

</body>
</html>