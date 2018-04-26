<!DOCTYPE html>
<html>
	<head>
		<title>Sistema de Alarme</title>
	</head>
	<body>
		<?php
			// Obtém o valor enviado pelo leitor via HTTP Request (GET Method).
			$distancia_media = $_GET["distancia_media"];
			// Cria uma conexão com o SGDB MySQL, utilizando a API MySQLi.
			$conexao = new mysqli("127.0.0.1", "monitor", "ifes2018", "ALARMSYS");
			// Verifica se ocorreram erros durante a criação da conexão.
			if (mysqli_connect_errno())
			{
				printf("Não foi possível conectar-se ao SGDB MySQL: %s\n", mysqli_connect_error());
				exit();
			}
			// Cria uma transação SQL.
			$transacao = $conexao->prepare("INSERT INTO DETECCAO (DETE_VL_DISTANCIA_MEDIA, DETE_DT_DETECCAO) VALUES (?, NOW());");
			// Associa, no script de transação SQL, os valores armazenados em variáveis de acordo
			// com o seu tipo ('d' define que o valor armazenado na variável é do tipo double).
			$transacao->bind_param('d', $distancia_media);
			// Executa a transação SQL.
			$transacao->execute();
			// Fecha a conexão com o SGDB.
			$conexao->close();
		?>
	</body>
</html>