/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package OS;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import static javax.swing.JFrame.setDefaultLookAndFeelDecorated;
import javax.swing.JLabel;
import javax.swing.JPanel;
import static javax.swing.UIManager.setLookAndFeel;
import javax.swing.border.TitledBorder;

/**
 *
 * @author Lau Dukang(laudukang@gmail.com)
 */
public class MyPath {

    public static JLabel jlb = new JLabel("广告位招租中……");

    public static JPanel addPath() throws Exception {
        setLookAndFeel("com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel");
        setDefaultLookAndFeelDecorated(true);
        JPanel p1 = new JPanel(new FlowLayout(FlowLayout.CENTER));
        Font font = new Font("TimesRoman", Font.BOLD, 15);
        TitledBorder title = new TitledBorder("");
        title.setTitleFont(font);
        title.setTitleColor(Color.BLACK);
        //jlb.setText(null);
        p1.setBorder(title);
        p1.add(jlb);
        return p1;
    }
}
