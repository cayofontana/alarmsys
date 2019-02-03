package observador;

import java.util.Map;
import java.util.HashMap;
import java.util.Date;
import java.util.Properties;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.SQLException;

class Deteccao
{
	private int id;
	private float valor;
	private Date data;

	private Connection conexao;
	private Properties propriedades;

	public Deteccao()
	{
		id = 0;
		valor = 0.0F;
		data = null;

		conexao = null;
		propriedades = new Properties();
		
		configurar();
	}

	public int getId()
	{
		return (id);
	}

	public String imprimir()
	{
		String strInfo;

		strInfo = "id: " + id + "\n";
		strInfo += "valor: " + valor + "\n";
		strInfo += "datahora: " + Util.obterTexto(data);

		System.out.println(strInfo);

		return (strInfo);
	}

	public Map<String, String> obterValores()
	{
		Map<String, String> valores = new HashMap<String, String>();

		valores.put("id", Integer.toString(id));
		valores.put("valor", Float.toString(valor));
		valores.put("datahora", Util.obterTexto(data));

		return (valores);
	}

	public void preencherUltima()
	{
		try
		{
			conexao = DriverManager.getConnection("jdbc:mysql://127.0.0.1/ALARMSYS?useSSL=false", propriedades);
			Statement consulta = conexao.createStatement();
			ResultSet conjuntoDados = consulta.executeQuery("SELECT DETE_ID_DETECCAO, DETE_VL_DISTANCIA_MEDIA, DETE_DT_DETECCAO FROM DETECCAO ORDER BY DETE_ID_DETECCAO DESC LIMIT 1");

			if (conjuntoDados.next())
			{
				id = conjuntoDados.getInt(1);
				valor = conjuntoDados.getFloat(2);
				data = Util.construirData(conjuntoDados.getString(3));
			}
			
			conexao.close();
		}
		catch (SQLException excecao)
		{
			System.out.println(excecao);
		}
	}

	private void configurar()
	{
		propriedades.put("user", "monitor");
		propriedades.put("password", "ifes2018");

		try
		{
			Class classe = Class.forName("com.mysql.jdbc.Driver");
			classe.newInstance();
		}
		catch (ClassNotFoundException excecao)
		{
			System.out.println(excecao);
		}
		catch (IllegalAccessException excecao)
		{
			System.out.println(excecao);
		}
		catch (InstantiationException excecao)
		{
			System.out.println(excecao);
		}
	}
}