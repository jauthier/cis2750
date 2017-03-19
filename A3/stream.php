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
<h2>Choose a Stream:</h2>
<?php
	$command = "./getStreams.py ".$username;
	exec($command, $output, $return);
	$i = 0;
	foreach($output as $stream)
		$i = $i+1;

	if ($i == 0)
		echo "You have not been added to any streams.";
?>

<?php if ($i != 0): ?>
<form method="post" action="readPost.php">
	<input type="hidden" name="username" value="<?php echo $username?>">
	<input type="hidden" name="action" value="-c">
	<input type="hidden" name="sort" value="-d">
	<input type="hidden" name="currentPost" value="-1">
	<?php
		foreach ($output as $stream) {
		 	echo "<input type=\"radio\" name=\"stream\" value=\"$stream\">$stream<br>";
		 }
	?>

	<input type="radio" name="stream" value="all">all<br>
	<input type="submit" value="View">
</form>
<?php endif ?>

</body>
</html>
