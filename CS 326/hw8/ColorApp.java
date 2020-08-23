
import java.util.List;
import java.util.ArrayList;
import java.util.Scanner;
import java.io.*;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.event.*;

class ColorPreview extends JComponent
{
	ColorApp frame;
	Color color;

	public ColorPreview( ColorApp f )
	{
		frame = f;
		color = Color.RED;
	}

	public void paint( Graphics g )
	{
		g.setColor( color );
		g.fillRect( 10, 10, 540, 400 );
	}

	public void setColor( Color c )
	{
		color = c;
		repaint();
	}
}

public class ColorApp extends JFrame
{
	protected JList< String > listColors;
	protected ColorPreview colorPreview;
	protected JLabel labelRed;
	protected JTextField tfRed;
	protected JButton buttonDecrRed;
	protected JButton buttonIncrRed;
	protected JLabel labelGreen;
	protected JTextField tfGreen;
	protected JButton buttonDecrGreen;
	protected JButton buttonIncrGreen;
	protected JLabel labelBlue;
	protected JTextField tfBlue;
	protected JButton buttonDecrBlue;
	protected JButton buttonIncrBlue;
	protected JButton buttonSave;
	protected JButton buttonReset;
	protected static String[] colorNames;
	protected static String[] colorNamesOriginal;
	protected static int[][] colorRgbCodes;
	protected static int selectedColor;
	protected static int r, g, b;

	public static void main( String[] args ) throws FileNotFoundException
	{
		Scanner file = new Scanner( new File( "colors.txt" ) );
		List< String > colors = new ArrayList< String >();
		List< int[] > rgbCodes = new ArrayList< int[] >();
		while ( file.hasNext() )
		{
			colors.add( file.next() );
			int r = Integer.parseInt( file.next() );
			int g = Integer.parseInt( file.next() );
			int b = Integer.parseInt( file.next() );
			int[] rgb = { r, g, b };
			rgbCodes.add( rgb );
		}
		file.close();
		colorNamesOriginal = colors.toArray( new String[ 0 ] );
		colorNames = colors.toArray( new String[ 0 ] );
		colorRgbCodes = new int[ rgbCodes.size() ][ 3 ];
		for ( int i = 0; i < rgbCodes.size(); i++ )
		{
			colorRgbCodes[ i ][ 0 ] = rgbCodes.get( i )[ 0 ];
			colorRgbCodes[ i ][ 1 ] = rgbCodes.get( i )[ 1 ];
			colorRgbCodes[ i ][ 2 ] = rgbCodes.get( i )[ 2 ];
		}
		r = colorRgbCodes[ 0 ][ 0 ];
		g = colorRgbCodes[ 0 ][ 1 ];
		b = colorRgbCodes[ 0 ][ 2 ];
		new ColorApp( "Color Sampler" );
	}

	public ColorApp( String title )
	{
		super( title );
		setSize( 900, 1000 );
		addWindowListener( new WindowDestroyer() );

		// JList color list
		listColors = new JList< String >();
		listColors.addListSelectionListener( new ListHandler() );
		listColors.setListData( colorNames );
		listColors.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		listColors.setBounds( 600, 20, 250, 880 );

		// JComponent color preview
		colorPreview = new ColorPreview( this );
		colorPreview.setColor( new Color( r, g, b ) );
		colorPreview.setBounds( 20, 20, 580, 400 );

		// JLabel red label
		labelRed = new JLabel( "Red:" );
		labelRed.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		labelRed.setBounds( 20, 450, 100, 50 );

		// JTextField red text field
		tfRed = new JTextField( Integer.toString( r ) );
		tfRed.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		tfRed.setBounds( 150, 450, 100, 50 );

		// JButton red decrement button
		buttonDecrRed = new JButton( "-" );
		buttonDecrRed.addActionListener( new ActionHandler() );
		buttonDecrRed.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		buttonDecrRed.setBounds( 300, 450, 100, 50 );

		// JButton red increment button
		buttonIncrRed = new JButton( "+" );
		buttonIncrRed.addActionListener( new ActionHandler() );
		buttonIncrRed.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		buttonIncrRed.setBounds( 450, 450, 100, 50 );

		// JLabel green label
		labelGreen = new JLabel( "Green:" );
		labelGreen.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		labelGreen.setBounds( 20, 550, 100, 50 );

		// JTextField green text field
		tfGreen = new JTextField( Integer.toString( g ) );
		tfGreen.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		tfGreen.setBounds( 150, 550, 100, 50 );

		// JButton green decrement button
		buttonDecrGreen = new JButton( "-" );
		buttonDecrGreen.addActionListener( new ActionHandler() );
		buttonDecrGreen.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		buttonDecrGreen.setBounds( 300, 550, 100, 50 );

		// JButton green increment button
		buttonIncrGreen = new JButton( "+" );
		buttonIncrGreen.addActionListener( new ActionHandler() );
		buttonIncrGreen.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		buttonIncrGreen.setBounds( 450, 550, 100, 50 );

		// JLabel blue label
		labelBlue = new JLabel( "Blue:" );
		labelBlue.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		labelBlue.setBounds( 20, 650, 100, 50 );

		// JTextField blue text field
		tfBlue = new JTextField( Integer.toString( b ) );
		tfBlue.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		tfBlue.setBounds( 150, 650, 100, 50 );

		// JButton blue decrement button
		buttonDecrBlue = new JButton( "-" );
		buttonDecrBlue.addActionListener( new ActionHandler() );
		buttonDecrBlue.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		buttonDecrBlue.setBounds( 300, 650, 100, 50 );

		// JButton blue increment button
		buttonIncrBlue = new JButton( "+" );
		buttonIncrBlue.addActionListener( new ActionHandler() );
		buttonIncrBlue.setFont( new Font( "Arial", Font.PLAIN, 30 ) );
		buttonIncrBlue.setBounds( 450, 650, 100, 50 );

		// JButton save button
		buttonSave = new JButton( "Save" );
		buttonSave.addActionListener( new ActionHandler() );
		buttonSave.setFont( new Font( "Arial", Font.PLAIN, 25 ) );
		buttonSave.setBounds( 100, 850, 150, 50 );

		// JButton reset button
		buttonReset = new JButton( "Reset" );
		buttonReset.addActionListener( new ActionHandler() );
		buttonReset.setFont( new Font( "Arial", Font.PLAIN, 25 ) );
		buttonReset.setBounds( 350, 850, 150, 50 );

		// add to pane
		getContentPane().setLayout( null );
		getContentPane().add( listColors );
		getContentPane().add( colorPreview );
		getContentPane().add( buttonSave );
		getContentPane().add( buttonReset );
		getContentPane().add( labelRed );
		getContentPane().add( tfRed );
		getContentPane().add( buttonDecrRed );
		getContentPane().add( buttonIncrRed );
		getContentPane().add( labelGreen );
		getContentPane().add( tfGreen );
		getContentPane().add( buttonDecrGreen );
		getContentPane().add( buttonIncrGreen );
		getContentPane().add( labelBlue );
		getContentPane().add( tfBlue );
		getContentPane().add( buttonDecrBlue );
		getContentPane().add( buttonIncrBlue );

		setVisible( true );
	}

	private class ListHandler implements ListSelectionListener
	{
		public void valueChanged( ListSelectionEvent e )
		{
			if ( e.getSource() == listColors )
				if ( !e.getValueIsAdjusting() )
				{
					int i = listColors.getSelectedIndex();
					if ( i != -1 )
					{
						ColorApp.this.setTitle( "Color Sampler" );
						colorNames[ selectedColor ] = colorNamesOriginal[ selectedColor ];
						listColors.setListData( colorNames );
						selectedColor = i;
						r = colorRgbCodes[ selectedColor ][ 0 ];
						g = colorRgbCodes[ selectedColor ][ 1 ];
						b = colorRgbCodes[ selectedColor ][ 2 ];
						tfRed.setText( Integer.toString( r ) );
						tfGreen.setText( Integer.toString( g ) );
						tfBlue.setText( Integer.toString( b ) );
						Color c = new Color( r, g, b );
						colorPreview.setColor( c );
					}
				}
		}
	}

	private class ActionHandler implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			if ( e.getSource() == buttonDecrRed )
			{
				ColorApp.this.setTitle( "Color Sampler*" );
				colorNames[ selectedColor ] = colorNamesOriginal[ selectedColor ] + "*";
				listColors.setListData( colorNames );
				if ( r >= 5 )
					r -= 5;
				Color c = new Color( r, g, b );
				colorPreview.setColor( c );
				tfRed.setText( Integer.toString( r ) );
			}
			else if ( e.getSource() == buttonIncrRed )
			{
				ColorApp.this.setTitle( "Color Sampler*" );
				colorNames[ selectedColor ] = colorNamesOriginal[ selectedColor ] + "*";
				listColors.setListData( colorNames );
				if ( r <= 250 )
					r += 5;
				Color c = new Color( r, g, b );
				colorPreview.setColor( c );
				tfRed.setText( Integer.toString( r ) );
			}
			else if ( e.getSource() == buttonDecrGreen )
			{
				ColorApp.this.setTitle( "Color Sampler*" );
				colorNames[ selectedColor ] = colorNamesOriginal[ selectedColor ] + "*";
				listColors.setListData( colorNames );
				if ( g >= 5 )
					g -= 5;
				Color c = new Color( r, g, b );
				colorPreview.setColor( c );
				tfGreen.setText( Integer.toString( g ) );
			}
			else if ( e.getSource() == buttonIncrGreen )
			{
				ColorApp.this.setTitle( "Color Sampler*" );
				colorNames[ selectedColor ] = colorNamesOriginal[ selectedColor ] + "*";
				listColors.setListData( colorNames );
				if ( g <= 250 )
					g += 5;
				Color c = new Color( r, g, b );
				colorPreview.setColor( c );
				tfGreen.setText( Integer.toString( g ) );
			}
			else if ( e.getSource() == buttonDecrBlue )
			{
				ColorApp.this.setTitle( "Color Sampler*" );
				colorNames[ selectedColor ] = colorNamesOriginal[ selectedColor ] + "*";
				listColors.setListData( colorNames );
				if ( b >= 5 )
					b -= 5;
				Color c = new Color( r, g, b );
				colorPreview.setColor( c );
				tfBlue.setText( Integer.toString( b ) );
			}
			else if ( e.getSource() == buttonIncrBlue )
			{
				ColorApp.this.setTitle( "Color Sampler*" );
				colorNames[ selectedColor ] = colorNamesOriginal[ selectedColor ] + "*";
				listColors.setListData( colorNames );
				if ( b <= 250 )
					b += 5;
				Color c = new Color( r, g, b );
				colorPreview.setColor( c );
				tfBlue.setText( Integer.toString( b ) );
			}
			else if ( e.getSource() == buttonSave )
			{
				colorRgbCodes[ selectedColor ][ 0 ] = r;
				colorRgbCodes[ selectedColor ][ 1 ] = g;
				colorRgbCodes[ selectedColor ][ 2 ] = b;
				ColorApp.this.setTitle( "Color Sampler" );
				colorNames[ selectedColor ] = colorNamesOriginal[ selectedColor ];
				listColors.setListData( colorNames );
			}
			else if ( e.getSource() == buttonReset )
			{
				r = colorRgbCodes[ selectedColor ][ 0 ];
				g = colorRgbCodes[ selectedColor ][ 1 ];
				b = colorRgbCodes[ selectedColor ][ 2 ];
				ColorApp.this.setTitle( "Color Sampler" );
				colorNames[ selectedColor ] = colorNamesOriginal[ selectedColor ];
				listColors.setListData( colorNames );
				tfRed.setText( Integer.toString( r ) );
				tfGreen.setText( Integer.toString( g ) );
				tfBlue.setText( Integer.toString( b ) );
				Color c = new Color( r, g, b );
				colorPreview.setColor( c );
			}
		}
	}

	private class WindowDestroyer extends WindowAdapter
	{
		public void windowClosing( WindowEvent e )
		{
			// Scanner file = new Scanner( new File( "colors.txt" ) );
			// while ( file.hasNext() )
			// {
			// 	colors.add( file.next() );
			// 	int r = Integer.parseInt( file.next() );
			// 	int g = Integer.parseInt( file.next() );
			// 	int b = Integer.parseInt( file.next() );
			// 	int[] rgb = { r, g, b };
			// 	rgbCodes.add( rgb );
			// }
			// file.close();
			try {
				FileWriter writer = new FileWriter( "colors.txt" );
				for ( int k = 0; k < colorNames.length; k++ )
					writer.write( colorNamesOriginal[ k ] + "\t" + colorRgbCodes[ k ][ 0 ] + " " + colorRgbCodes[ k ][ 1 ] + " " + colorRgbCodes[ k ][ 2 ] + "\n" );
				writer.close();
			}
			catch (IOException ioe) {}
			System.exit( 0 );
		}
	}
}
