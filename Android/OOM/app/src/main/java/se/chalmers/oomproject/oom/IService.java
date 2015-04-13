package se.chalmers.oomproject.oom;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.media.Image;
import android.os.Environment;

import java.io.File;

/**
 * Created by meddan on 13/03/15.
 */
public interface IService {
    public String getName();
    public Drawable getLogo(Context c);
    public Drawable getOtherLogo(Context c);

    public class Steam implements IService{
        private String name;
        public Steam(){
            this.name = "Steam";
        }
        @Override
        public String getName() {
            return name;
        }

        @Override
        public Drawable getLogo(Context c) {
            return c.getResources().getDrawable(c.getResources().getIdentifier("steam", "drawable", c.getPackageName()));
        }

        @Override
        public Drawable getOtherLogo(Context c) {
            return c.getResources().getDrawable(c.getResources().getIdentifier("steamdark", "drawable", c.getPackageName()));
        }
    }
    public class Facebook implements IService{
        private String name;
        public Facebook(){
            this.name = "Facebook";
        }

        @Override
        public String getName() {
            return name;
        }

        @Override
        public Drawable getLogo(Context c) {
            return c.getResources().getDrawable(c.getResources().getIdentifier("fb", "drawable", c.getPackageName()));
        }

        @Override
        public Drawable getOtherLogo(Context c) {
            return c.getResources().getDrawable(c.getResources().getIdentifier("fbdark", "drawable", c.getPackageName()));
        }
    }
}
