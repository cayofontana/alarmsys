package imp.modelo;

import java.util.List;
import java.util.ArrayList;
import java.util.Date;

import imp.infraestrutura.Util;
import imp.modelo.persistencia.AcessoDados;

public class Token
{
	private String id;
	private Date data;

	private AcessoDados acessoDados;

	public Token(AcessoDados acessoDados)
	{
		this.acessoDados = acessoDados;
	}

	private Token()
	{
	}

	public String getId()
	{
		return (id);
	}

	public List<Token> listar()
	{
		List<Token> tokens = new ArrayList<>();
		Token token = null;
		List<String> objetos = new ArrayList<>();
		String sqlConsulta;
		int quantidadeColunas = 0;

		sqlConsulta = "SELECT ";
		sqlConsulta += "TOKE_ID_TOKEN, ";
		quantidadeColunas++;
		sqlConsulta += "TOKE_DT_CADASTRO ";
		quantidadeColunas++;
		sqlConsulta += "FROM TOKEN;";

		objetos = acessoDados.listar(sqlConsulta);

		for (int i = 0; i < objetos.size(); ++i)
		{
			if (i % quantidadeColunas == 0)
			{
				token = new Token();
				tokens.add(token);
			}

			switch (i)
			{
				case 0:
					token.id = objetos.get(i);
					break;
				case 1:
					token.data = Util.construirData(objetos.get(i));
					break;
			}
		}

		return (tokens);
	}
}