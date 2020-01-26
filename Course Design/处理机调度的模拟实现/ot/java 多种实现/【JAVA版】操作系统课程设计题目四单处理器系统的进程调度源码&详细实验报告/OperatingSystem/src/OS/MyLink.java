/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package OS;

import java.awt.Cursor;
import java.awt.Desktop;
import static java.awt.Desktop.getDesktop;
import static java.awt.Desktop.isDesktopSupported;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.net.URISyntaxException;
import javax.swing.JLabel;

/**
 *
 * @author Lau Dukang(laudukang@gmail.com)
 */
public class MyLink extends JLabel {

    private String text, url;
    private boolean isSupported;

    public MyLink(String text, String url) {
        this.text = text;
        this.url = url;
        try {
            this.isSupported = isDesktopSupported()
                    && getDesktop().isSupported(Desktop.Action.BROWSE);
        } catch (Exception e) {
            this.isSupported = false;
        }
        setText(false);
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                setText(isSupported);
                if (isSupported) {
                    setCursor(new Cursor(Cursor.HAND_CURSOR));
                }
            }

            @Override
            public void mouseExited(MouseEvent e) {
                setText(false);
            }

            @Override
            public void mouseClicked(MouseEvent e) {
                try {
                    getDesktop().browse(
                            new java.net.URI(MyLink.this.url));
                } catch (URISyntaxException | IOException ex) {
                    System.out.println("´ò¿ª³¬Á´½Ó´íÎó£º" + ex.toString());
                }
            }
        });
    }

    private void setText(boolean b) {
        if (!b) {
            setText("<html><font color=blue><u>" + text);
        } else {
            setText("<html><font color=red><u>" + text);
        }
    }
}
