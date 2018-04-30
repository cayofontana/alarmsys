<%@ page import = "java.sql.Connection"%>
<%@ page import = "java.sql.DriverManager"%>
<%@ page import = "java.sql.Statement"%>
<%@ page import = "java.sql.SQLException"%>

<html>
	<head>
		<title>Cadastro de Deteccao</title>
	</head>
	<body>
		<%
			try
			{
				float distanciaMedia = Float.parseFloat(request.getParameter("distancia_media"));
				Class.forName("com.mysql.jdbc.Driver").newInstance(); 
				Connection conexao = DriverManager.getConnection("jdbc:mysql://127.0.0.1/ALARMSYS", "monitor", "ifes2018");
				Statement consulta = conexao.createStatement();
				consulta.execute("INSERT INTO DETECCAO (DETE_VL_DISTANCIA_MEDIA, DETE_DT_DETECCAO) VALUES (" + distanciaMedia + ", NOW());");
				conexao.close();
			}
			catch (SQLException excecao)
			{
				out.println("Erro ao inserir novo registro: " + excecao);
			}
		%>
	</body>
</html>