import java.util.Date;

import java.text.SimpleDateFormat;
import java.text.ParseException;

class Util
{
	private static SimpleDateFormat formatoData;

	static
	{
		formatoData = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	}

	public static Date construirData(String strMySQLDataHora)
	{
		Date data;
		String dia, mes, ano, hora, minuto, segundo;

		data = null;
		try
		{
			ano = strMySQLDataHora.substring(0, 4);
			mes = strMySQLDataHora.substring(5, 7);
			dia = strMySQLDataHora.substring(8, 10);
			
			hora = strMySQLDataHora.substring(11, 13);
			minuto = strMySQLDataHora.substring(14, 16);
			segundo = strMySQLDataHora.substring(17, 19);

			data = formatoData.parse(ano + "-" + mes + "-" + dia + " " + hora + ":" + minuto + ":" + segundo);
		}
		catch (ParseException excecao)
		{
			System.out.println(excecao);
		}
		catch (StringIndexOutOfBoundsException excecao)
		{
			System.out.println(excecao);
		}
		finally
		{
			return (data);
		}
	}

	public static String obterTexto(Date data)
	{
		return (formatoData.format(data));
	}
}