<!DOCTYPE html>

<html>
<head>
<?php 
	$username = $_POST["username"];
 	$stream = $_POST["stream"];
 ?>
<title><?php echo $stream; ?></title>
</head>

<body>

<h3>Welcome <?php echo $username; ?></h3>



<form>
	<input type="submit" value="Next">
	<input type="submit" value="Previous">
	<input type="submit" value="New Stream">
	<input type="submit" value="Logout">
</form>

</body>
</html>