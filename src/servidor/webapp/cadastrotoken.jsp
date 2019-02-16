<!DOCTYPE html>

<%@ page import = "java.sql.Connection"%>
<%@ page import = "java.sql.DriverManager"%>
<%@ page import = "java.sql.Statement"%>
<%@ page import = "java.sql.SQLException"%>

<html>
	<head>
		<title>Cadastro de Tokens</title>
	</head>
	<body>
		<%
			if (request.getParameter("token") == null) {
				out.println("<form action=\"cadastrotoken.jsp\" method=\"POST\">");
				out.println("<div>");
				out.println("Token: <input type=\"text\" size=\"152\" name=\"token\" minlength=\"152\" maxlength=\"152\" autofocus required>");
				out.println("<input type=\"submit\" value=\"Enviar\">");
				out.println("</div>");
				out.println("</form>");
			}
			else {
				try
				{
					String token = request.getParameter("token");

					Class.forName("com.mysql.jdbc.Driver").newInstance(); 
					Connection conexao = DriverManager.getConnection("jdbc:mysql://127.0.0.1/ALARMSYS", "monitor", "ifes2018");
					Statement consulta = conexao.createStatement();
					consulta.execute("INSERT INTO TOKEN (TOKE_ID_TOKEN, TOKE_DT_CADASTRO) VALUES ('" + token + "', NOW());");
					conexao.close();
					out.println("Token inserido com sucesso!");
				}
				catch (SQLException excecao)
				{
					out.println("Erro ao inserir novo registro: " + excecao);
				}
				finally
				{
					request.removeAttribute("token");
				}
			}
		%>
	</body>
</html>