<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8" />
<title>Page de test</title>
   <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
	<h1>Insertion d'album</h1>
	<form method="post" action="bdd.php">
		<p>
			<label for="nomA">Nom Album : </label> <input type="text" name="nomA" id="nomA" />
			<br />
			<label for="label">Label : </label> 
			<select name="label" id="label">

			<?php
				$bdd = new PDO('mysql:host=localhost;dbname=chanteur;', 'root', '');
				$requete = $bdd->query("SELECT distinct(label) FROM album ORDER BY label");
				while($donnees = $requete->fetch()) {
					echo '<option value="'.$donnees['label'].'">'.$donnees['label'].'</option>';
				}
				
				
			?>
			</select>
			<br />
			<input type="submit" name="insert" value="Insérer" />
		</p>
	</form>

</body>
</html>