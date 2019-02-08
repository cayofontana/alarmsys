package imp.modelo.persistencia;

import java.util.List;
import java.util.ArrayList;
import java.util.Properties;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;

import java.lang.reflect.InvocationTargetException;

public class AcessoDados
{
	private Connection conexao;
	private Properties propriedades;

	public AcessoDados()
	{
		conexao = null;
		propriedades = new Properties();

		inicializar();
	}

	public List<String> listar(String sqlConsulta)
	{
		List<String> objetos = new ArrayList<>();

		try
		{
			conexao = DriverManager.getConnection("jdbc:mysql://127.0.0.1/ALARMSYS?useSSL=false", propriedades);
			Statement consulta = conexao.createStatement();
			ResultSet conjuntoDados = consulta.executeQuery(sqlConsulta);

			while (conjuntoDados.next())
				for (int i = 1; i <= conjuntoDados.getMetaData().getColumnCount(); ++i)
					objetos.add(conjuntoDados.getString(i));
		}
		catch (SQLException excecao)
		{
			System.out.println(excecao);
		}

		return (objetos);
	}

	private void inicializar()
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