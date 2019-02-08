package imp.modelo;

import java.util.List;
import java.util.ArrayList;
import java.util.Date;
import java.util.Properties;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;

import java.lang.reflect.InvocationTargetException;

import imp.infraestrutura.Util;	

public class Token
{
	private String id;
	private Date data;

	private static Connection conexao;
	private static Properties propriedades;

	public Token(String id, Date data)
	{
		this.id = id;
		this.data = data;
	}

	public String getId()
	{
		return (id);
	}

	public String imprimir()
	{
		String strInfo;

		strInfo = "id: " + id + "\n";
		strInfo += "datahora: " + Util.obterTexto(data);

		System.out.println(strInfo);

		return (strInfo);
	}

	public static List<Token> listar()
	{
		List<Token> tokens = new ArrayList<>();

		try
		{
			configurar();
			conexao = DriverManager.getConnection("jdbc:mysql://127.0.0.1/ALARMSYS?useSSL=false", propriedades);
			Statement consulta = conexao.createStatement();
			ResultSet conjuntoDados = consulta.executeQuery("SELECT TOKE_ID_TOKEN, TOKE_DT_CADASTRO FROM TOKEN");

			while (conjuntoDados.next())
				tokens.add(new Token(conjuntoDados.getString(1), Util.construirData(conjuntoDados.getString(2))));
			
			conexao.close();
		}
		catch (SQLException excecao)
		{
			System.out.println(excecao);
		}

		return (tokens);
	}

	private static void configurar()
	{
		conexao = null;
		propriedades = new Properties();

		propriedades.put("user", "monitor");
		propriedades.put("password", "ifes2018");

		try
		{
			Class<?> classe = Class.forName("com.mysql.jdbc.Driver");
			classe.getDeclaredConstructor().newInstance();
		}
		catch (ClassNotFoundException excecao)
		{
			System.out.println(excecao);
		}
		catch (IllegalAccessException excecao)
		{
			System.out.println(excecao);
		}
		catch (NoSuchMethodException excecao)
		{
			System.out.println(excecao);
		}
		catch (InstantiationException excecao)
		{
			System.out.println(excecao);
		}
		catch (InvocationTargetException excecao)
		{
			System.out.println(excecao);
		}
	}
}