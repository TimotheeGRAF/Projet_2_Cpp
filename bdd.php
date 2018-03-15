<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8" />
<title>Page de test</title>
   <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>
<?php
	$bdd = new PDO('mysql:host=localhost;dbname=chanteur;', 'root', '');
	if(isset($_POST['insert'])) {
		$nomA = htmlspecialchars($_POST['nomA']);
		$label = htmlspecialchars($_POST['label']);
		
		$insert = "INSERT INTO album VALUES (NULL, '$nomA', '$label')";
		$bdd->exec($insert);
		echo affichTab();
	}
	elseif(isset($_POST['editer'])) {
		$idA = $_POST['num_album'];
		$nomA = $_POST['nomA'];
		$label = $_POST['label'];

		$update = "UPDATE album SET nom_album='$nomA', label='$label' WHERE num_album=$idA";
		$bdd->exec($update);
		echo affichTab();
	}
	elseif(isset($_GET['action'])) {
		if($_GET['action'] == "editer") {
			$idAlbum = $_GET['num_album'];
			$requete = $bdd->query("SELECT * FROM album WHERE num_album = $id");
			while($d = $requete->fetch()) {
				$nomA = $d['nom_album'];
				$label = $d['label'];
			}
			?>
				<form method="post" action="bdd.php">
					<p>
						<input type="hidden" name="num_album" value="<?= $idAlbum ?>" />
						<label for="nomA">Nom Album : </label> <input type="text" name="nomA" id="nomA" value="<?= $nomA ?>" />
						<br />
						<label for="label">Label : </label> 
						<select name="label" id="label">

						<?php
							$bdd = new PDO('mysql:host=localhost;dbname=chanteur;', 'root', '');
							$requete = $bdd->query("SELECT distinct(label) FROM album ORDER BY label");
							while($donnees = $requete->fetch()) {
								if ($label == $donnees['label']) {
									echo '<option value="'.$donnees['label'].'" selected>'.$donnees['label'].'</option>';
								}
								else {
									echo '<option value="'.$donnees['label'].'">'.$donnees['label'].'</option>';
								}
							}
							
							
						?>
						</select>
						<br />
						<input type="submit" name="editer" value="&Eacute;diter" />
					</p>
				</form>
			
			<?php
		}
		elseif($_GET['action'] == "supprimer") {
			$id = $_GET['num_album'];
			$delete = "DELETE FROM album where num_album=$id";
			$bdd->exec($delete);
		echo affichTab();
		}
		else {
			echo affichTab();
		}
	}
	else {
		echo affichTab();
	}
	
	
	function affichTab() {
		$bdd = new PDO('mysql:host=localhost;dbname=chanteur;', 'root', '');
		$tableau= "<table>
				<tr><th>Num album</th><th>Nom album</th><th>Label</th><th>&Eacute;diter</th><th>Supprimer</th></tr>";
		$requete = $bdd->query("SELECT * FROM album");
		while($donnees = $requete->fetch()) {
			$tableau .= "<tr>
							<td>".$donnees['num_album']."</td>
							<td>".$donnees['nom_album']."</td>
							<td>".$donnees['label']."</td>
							<td><a href='bdd.php?action=editer&amp;num_album=".$donnees['num_album']."'>&Eacute;diter</a></td>
							<td><a href='bdd.php?action=supprimer&amp;num_album=".$donnees['num_album']."'>Supprimer</a></td>
						</tr>";
		}
		$tableau .= "</table>";
		$tableau .= "<p><a href='form.php'>Ajouter un nouvel album</a></p>";
		return $tableau;
	}
?>



</body>
</html>